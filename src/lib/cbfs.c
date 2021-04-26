/* SPDX-License-Identifier: GPL-2.0-only */

#include <assert.h>
#include <boot_device.h>
#include <cbfs.h>
#include <cbfs_private.h>
#include <cbmem.h>
#include <commonlib/bsd/compression.h>
#include <commonlib/endian.h>
#include <console/console.h>
#include <fmap.h>
#include <lib.h>
#include <metadata_hash.h>
#include <security/tpm/tspi/crtm.h>
#include <security/vboot/vboot_common.h>
#include <stdlib.h>
#include <string.h>
#include <symbols.h>
#include <timestamp.h>

#if CBFS_CACHE_AVAILABLE
struct mem_pool cbfs_cache = MEM_POOL_INIT(_cbfs_cache, REGION_SIZE(cbfs_cache));

static void switch_to_postram_cache(int unused)
{
	if (_preram_cbfs_cache != _postram_cbfs_cache)
		mem_pool_init(&cbfs_cache, _postram_cbfs_cache,
			      REGION_SIZE(postram_cbfs_cache));
}
ROMSTAGE_CBMEM_INIT_HOOK(switch_to_postram_cache);
#endif

cb_err_t cbfs_boot_lookup(const char *name, bool force_ro,
			  union cbfs_mdata *mdata, struct region_device *rdev)
{
	const struct cbfs_boot_device *cbd = cbfs_get_boot_device(force_ro);
	if (!cbd)
		return CB_ERR;

	size_t data_offset;
	cb_err_t err = CB_CBFS_CACHE_FULL;
	if (!CONFIG(NO_CBFS_MCACHE) && !ENV_SMM && cbd->mcache_size)
		err = cbfs_mcache_lookup(cbd->mcache, cbd->mcache_size,
					 name, mdata, &data_offset);
	if (err == CB_CBFS_CACHE_FULL) {
		struct vb2_hash *metadata_hash = NULL;
		if (CONFIG(TOCTOU_SAFETY)) {
			if (ENV_SMM)  /* Cannot provide TOCTOU safety for SMM */
				dead_code();
			if (!cbd->mcache_size)
				die("Cannot access CBFS TOCTOU-safely in " ENV_STRING " before CBMEM init!\n");
			/* We can only reach this for the RW CBFS -- an mcache overflow in the
			   RO CBFS would have been caught when building the mcache in cbfs_get
			   boot_device(). (Note that TOCTOU_SAFETY implies !NO_CBFS_MCACHE.) */
			assert(cbd == vboot_get_cbfs_boot_device());
			/* TODO: set metadata_hash to RW metadata hash here. */
		}
		err = cbfs_lookup(&cbd->rdev, name, mdata, &data_offset, metadata_hash);
	}

	if (CONFIG(VBOOT_ENABLE_CBFS_FALLBACK) && !force_ro && err == CB_CBFS_NOT_FOUND) {
		printk(BIOS_INFO, "CBFS: Fall back to RO region for %s\n", name);
		return cbfs_boot_lookup(name, true, mdata, rdev);
	}
	if (err) {
		if (err == CB_CBFS_NOT_FOUND)
			printk(BIOS_WARNING, "CBFS: '%s' not found.\n", name);
		else if (err == CB_CBFS_HASH_MISMATCH)
			printk(BIOS_ERR, "CBFS ERROR: metadata hash mismatch!\n");
		else
			printk(BIOS_ERR, "CBFS ERROR: error %d when looking up '%s'\n",
			       err, name);
		return err;
	}

	if (rdev_chain(rdev, &cbd->rdev, data_offset, be32toh(mdata->h.len)))
		return CB_ERR;

	if (tspi_measure_cbfs_hook(rdev, name, be32toh(mdata->h.type))) {
		printk(BIOS_ERR, "CBFS ERROR: error when measuring '%s'\n", name);
	}

	return CB_SUCCESS;
}

int cbfs_boot_locate(struct cbfsf *fh, const char *name, uint32_t *type)
{
	if (cbfs_boot_lookup(name, false, &fh->mdata, &fh->data))
		return -1;

	size_t msize = be32toh(fh->mdata.h.offset);
	if (rdev_chain_mem(&fh->metadata, &fh->mdata, msize))
		return -1;

	if (type) {
		if (!*type)
			*type = be32toh(fh->mdata.h.type);
		else if (*type != be32toh(fh->mdata.h.type))
			return -1;
	}

	return 0;
}

void cbfs_unmap(void *mapping)
{
	/*
	 * This is save to call with mappings that weren't allocated in the cache (e.g. x86
	 * direct mappings) -- mem_pool_free() just does nothing for addresses it doesn't
	 * recognize. This hardcodes the assumption that if platforms implement an rdev_mmap()
	 * that requires a free() for the boot_device, they need to implement it via the
	 * cbfs_cache mem_pool.
	 */
	if (CBFS_CACHE_AVAILABLE)
		mem_pool_free(&cbfs_cache, mapping);
}

int cbfs_locate_file_in_region(struct cbfsf *fh, const char *region_name,
			       const char *name, uint32_t *type)
{
	struct region_device rdev;
	int ret = 0;
	if (fmap_locate_area_as_rdev(region_name, &rdev)) {
		LOG("%s region not found while looking for %s\n", region_name, name);
		return -1;
	}

	uint32_t dummy_type = 0;
	if (!type)
		type = &dummy_type;

	ret = cbfs_locate(fh, &rdev, name, type);
	if (!ret)
		if (tspi_measure_cbfs_hook(&rdev, name, *type))
			LOG("error measuring %s in region %s\n", name, region_name);
	return ret;
}

static inline bool fsps_env(void)
{
	/* FSP-S is assumed to be loaded in ramstage. */
	if (ENV_RAMSTAGE)
		return true;
	return false;
}

static inline bool fspm_env(void)
{
	/* FSP-M is assumed to be loaded in romstage. */
	if (ENV_ROMSTAGE)
		return true;
	return false;
}

static inline bool cbfs_lz4_enabled(void)
{
	if (fsps_env() && CONFIG(FSP_COMPRESS_FSP_S_LZ4))
		return true;
	if (fspm_env() && CONFIG(FSP_COMPRESS_FSP_M_LZ4))
		return true;

	if ((ENV_BOOTBLOCK || ENV_SEPARATE_VERSTAGE) && !CONFIG(COMPRESS_PRERAM_STAGES))
		return false;

	if (ENV_SMM)
		return false;

	return true;
}

static inline bool cbfs_lzma_enabled(void)
{
	if (fsps_env() && CONFIG(FSP_COMPRESS_FSP_S_LZMA))
		return true;
	if (fspm_env() && CONFIG(FSP_COMPRESS_FSP_M_LZMA))
		return true;
	/* We assume here romstage and postcar are never compressed. */
	if (ENV_BOOTBLOCK || ENV_SEPARATE_VERSTAGE)
		return false;
	if (ENV_ROMSTAGE && CONFIG(POSTCAR_STAGE))
		return false;
	if ((ENV_ROMSTAGE || ENV_POSTCAR) && !CONFIG(COMPRESS_RAMSTAGE))
		return false;
	if (ENV_SMM)
		return false;
	return true;
}

static inline bool cbfs_file_hash_mismatch(const void *buffer, size_t size,
					   const struct vb2_hash *file_hash)
{
	/* Avoid linking hash functions when verification is disabled. */
	if (!CONFIG(CBFS_VERIFICATION))
		return false;

	/* If there is no file hash, always count that as a mismatch. */
	if (file_hash && vb2_hash_verify(buffer, size, file_hash) == VB2_SUCCESS)
		return false;

	printk(BIOS_CRIT, "CBFS file hash mismatch!\n");
	return true;
}

static size_t cbfs_load_and_decompress(const struct region_device *rdev, void *buffer,
				       size_t buffer_size, uint32_t compression,
				       const struct vb2_hash *file_hash)
{
	size_t in_size = region_device_sz(rdev);
	size_t out_size = 0;
	void *map;

	DEBUG("Decompressing %zu bytes to %p with algo %d\n", in_size, buffer, compression);

	switch (compression) {
	case CBFS_COMPRESS_NONE:
		if (buffer_size < in_size)
			return 0;
		if (rdev_readat(rdev, buffer, 0, in_size) != in_size)
			return 0;
		if (cbfs_file_hash_mismatch(buffer, in_size, file_hash))
			return 0;
		return in_size;

	case CBFS_COMPRESS_LZ4:
		if (!cbfs_lz4_enabled())
			return 0;

		/* cbfs_prog_stage_load() takes care of in-place LZ4 decompression by
		   setting up the rdev to be in memory. */
		map = rdev_mmap_full(rdev);
		if (map == NULL)
			return 0;

		if (!cbfs_file_hash_mismatch(map, in_size, file_hash)) {
			timestamp_add_now(TS_START_ULZ4F);
			out_size = ulz4fn(map, in_size, buffer, buffer_size);
			timestamp_add_now(TS_END_ULZ4F);
		}

		rdev_munmap(rdev, map);

		return out_size;

	case CBFS_COMPRESS_LZMA:
		if (!cbfs_lzma_enabled())
			return 0;
		map = rdev_mmap_full(rdev);
		if (map == NULL)
			return 0;

		if (!cbfs_file_hash_mismatch(map, in_size, file_hash)) {
			/* Note: timestamp not useful for memory-mapped media (x86) */
			timestamp_add_now(TS_START_ULZMA);
			out_size = ulzman(map, in_size, buffer, buffer_size);
			timestamp_add_now(TS_END_ULZMA);
		}

		rdev_munmap(rdev, map);

		return out_size;

	default:
		return 0;
	}
}

static inline int tohex4(unsigned int c)
{
	return (c <= 9) ? (c + '0') : (c - 10 + 'a');
}

static void tohex8(unsigned int val, char *dest)
{
	dest[0] = tohex4((val >> 4) & 0xf);
	dest[1] = tohex4(val & 0xf);
}

static void tohex16(unsigned int val, char *dest)
{
	dest[0] = tohex4(val >> 12);
	dest[1] = tohex4((val >> 8) & 0xf);
	dest[2] = tohex4((val >> 4) & 0xf);
	dest[3] = tohex4(val & 0xf);
}

void *cbfs_boot_map_optionrom(uint16_t vendor, uint16_t device)
{
	char name[17] = "pciXXXX,XXXX.rom";

	tohex16(vendor, name + 3);
	tohex16(device, name + 8);

	return cbfs_map(name, NULL);
}

void *cbfs_boot_map_optionrom_revision(uint16_t vendor, uint16_t device, uint8_t rev)
{
	char name[20] = "pciXXXX,XXXX,XX.rom";

	tohex16(vendor, name + 3);
	tohex16(device, name + 8);
	tohex8(rev, name + 13);

	return cbfs_map(name, NULL);
}

void *_cbfs_alloc(const char *name, cbfs_allocator_t allocator, void *arg,
		  size_t *size_out, bool force_ro, enum cbfs_type *type)
{
	struct region_device rdev;
	union cbfs_mdata mdata;
	void *loc;

	DEBUG("%s(name='%s', alloc=%p(%p), force_ro=%s, type=%d)\n", __func__, name, allocator,
	      arg, force_ro ? "true" : "false", type ? *type : -1);

	if (cbfs_boot_lookup(name, force_ro, &mdata, &rdev))
		return NULL;

	if (type) {
		const enum cbfs_type real_type = be32toh(mdata.h.type);
		if (*type == CBFS_TYPE_QUERY)
			*type = real_type;
		else if (*type != real_type) {
			ERROR("'%s' type mismatch (is %u, expected %u)\n",
			      mdata.h.filename, real_type, *type);
			return NULL;
		}
	}

	size_t size = region_device_sz(&rdev);
	uint32_t compression = CBFS_COMPRESS_NONE;
	const struct cbfs_file_attr_compression *cattr = cbfs_find_attr(&mdata,
				CBFS_FILE_ATTR_TAG_COMPRESSION, sizeof(*cattr));
	if (cattr) {
		compression = be32toh(cattr->compression);
		size = be32toh(cattr->decompressed_size);
	}

	if (size_out)
		*size_out = size;

	const struct vb2_hash *file_hash = NULL;
	if (CONFIG(CBFS_VERIFICATION))
		file_hash = cbfs_file_hash(&mdata);

	/* allocator == NULL means do a cbfs_map() */
	if (allocator) {
		loc = allocator(arg, size, &mdata);
	} else if (compression == CBFS_COMPRESS_NONE) {
		void *mapping = rdev_mmap_full(&rdev);
		if (!mapping || cbfs_file_hash_mismatch(mapping, size, file_hash))
			return NULL;
		return mapping;
	} else if (!CBFS_CACHE_AVAILABLE) {
		ERROR("Cannot map compressed file %s on x86\n", mdata.h.filename);
		return NULL;
	} else {
		loc = mem_pool_alloc(&cbfs_cache, size);
	}

	if (!loc) {
		ERROR("'%s' allocation failure\n", mdata.h.filename);
		return NULL;
	}

	size = cbfs_load_and_decompress(&rdev, loc, size, compression, file_hash);
	if (!size)
		return NULL;

	return loc;
}

void *_cbfs_default_allocator(void *arg, size_t size, const union cbfs_mdata *unused)
{
	struct _cbfs_default_allocator_arg *darg = arg;
	if (size > darg->buf_size)
		return NULL;
	return darg->buf;
}

void *_cbfs_cbmem_allocator(void *arg, size_t size, const union cbfs_mdata *unused)
{
	return cbmem_add((uintptr_t)arg, size);
}

cb_err_t cbfs_prog_stage_load(struct prog *pstage)
{
	union cbfs_mdata mdata;
	struct region_device rdev;
	cb_err_t err;

	prog_locate_hook(pstage);

	if ((err = cbfs_boot_lookup(prog_name(pstage), false, &mdata, &rdev)))
		return err;

	assert(be32toh(mdata.h.type) == CBFS_TYPE_STAGE);
	pstage->cbfs_type = CBFS_TYPE_STAGE;

	enum cbfs_compression compression = CBFS_COMPRESS_NONE;
	const struct cbfs_file_attr_compression *cattr = cbfs_find_attr(&mdata,
				CBFS_FILE_ATTR_TAG_COMPRESSION, sizeof(*cattr));
	if (cattr)
		compression = be32toh(cattr->compression);

	const struct cbfs_file_attr_stageheader *sattr = cbfs_find_attr(&mdata,
				CBFS_FILE_ATTR_TAG_STAGEHEADER, sizeof(*sattr));
	if (!sattr)
		return CB_ERR;
	prog_set_area(pstage, (void *)(uintptr_t)be64toh(sattr->loadaddr),
		      be32toh(sattr->memlen));
	prog_set_entry(pstage, prog_start(pstage) +
			       be32toh(sattr->entry_offset), NULL);

	const struct vb2_hash *file_hash = NULL;
	if (CONFIG(CBFS_VERIFICATION))
		file_hash = cbfs_file_hash(&mdata);

	/* Hacky way to not load programs over read only media. The stages
	 * that would hit this path initialize themselves. */
	if ((ENV_BOOTBLOCK || ENV_SEPARATE_VERSTAGE) &&
	    !CONFIG(NO_XIP_EARLY_STAGES) && CONFIG(BOOT_DEVICE_MEMORY_MAPPED)) {
		void *mapping = rdev_mmap_full(&rdev);
		rdev_munmap(&rdev, mapping);
		if (cbfs_file_hash_mismatch(mapping, region_device_sz(&rdev), file_hash))
			return CB_CBFS_HASH_MISMATCH;
		if (mapping == prog_start(pstage))
			return CB_SUCCESS;
	}

	/* LZ4 stages can be decompressed in-place to save mapping scratch space. Load the
	   compressed data to the end of the buffer and point &rdev to that memory location. */
	if (cbfs_lz4_enabled() && compression == CBFS_COMPRESS_LZ4) {
		size_t in_size = region_device_sz(&rdev);
		void *compr_start = prog_start(pstage) + prog_size(pstage) - in_size;
		if (rdev_readat(&rdev, compr_start, 0, in_size) != in_size)
			return CB_ERR;
		rdev_chain_mem(&rdev, compr_start, in_size);
	}

	size_t fsize = cbfs_load_and_decompress(&rdev, prog_start(pstage), prog_size(pstage),
						compression, file_hash);
	if (!fsize)
		return CB_ERR;

	/* Clear area not covered by file. */
	memset(prog_start(pstage) + fsize, 0, prog_size(pstage) - fsize);

	prog_segment_loaded((uintptr_t)prog_start(pstage), prog_size(pstage),
			    SEG_FINAL);

	return CB_SUCCESS;
}

void cbfs_boot_device_find_mcache(struct cbfs_boot_device *cbd, uint32_t id)
{
	if (CONFIG(NO_CBFS_MCACHE) || ENV_SMM)
		return;

	if (cbd->mcache_size)
		return;

	const struct cbmem_entry *entry;
	if (cbmem_possibly_online() &&
	    (entry = cbmem_entry_find(id))) {
		cbd->mcache = cbmem_entry_start(entry);
		cbd->mcache_size = cbmem_entry_size(entry);
	} else if (ENV_ROMSTAGE_OR_BEFORE) {
		u8 *boundary = _ecbfs_mcache - REGION_SIZE(cbfs_mcache) *
			CONFIG_CBFS_MCACHE_RW_PERCENTAGE / 100;
		boundary = (u8 *)ALIGN_DOWN((uintptr_t)boundary, CBFS_MCACHE_ALIGNMENT);
		if (id == CBMEM_ID_CBFS_RO_MCACHE) {
			cbd->mcache = _cbfs_mcache;
			cbd->mcache_size = boundary - _cbfs_mcache;
		} else if (id == CBMEM_ID_CBFS_RW_MCACHE) {
			cbd->mcache = boundary;
			cbd->mcache_size = _ecbfs_mcache - boundary;
		}
	}
}

cb_err_t cbfs_init_boot_device(const struct cbfs_boot_device *cbd,
			       struct vb2_hash *mdata_hash)
{
	/* If we have an mcache, mcache_build() will also check mdata hash. */
	if (!CONFIG(NO_CBFS_MCACHE) && !ENV_SMM && cbd->mcache_size > 0)
		return cbfs_mcache_build(&cbd->rdev, cbd->mcache, cbd->mcache_size, mdata_hash);

	/* No mcache and no verification means we have nothing special to do. */
	if (!CONFIG(CBFS_VERIFICATION) || !mdata_hash)
		return CB_SUCCESS;

	/* Verification only: use cbfs_walk() without a walker() function to just run through
	   the CBFS once, will return NOT_FOUND by default. */
	cb_err_t err = cbfs_walk(&cbd->rdev, NULL, NULL, mdata_hash, 0);
	if (err == CB_CBFS_NOT_FOUND)
		err = CB_SUCCESS;
	return err;
}

const struct cbfs_boot_device *cbfs_get_boot_device(bool force_ro)
{
	static struct cbfs_boot_device ro;

	/* Ensure we always init RO mcache, even if the first file is from the RW CBFS.
	   Otherwise it may not be available when needed in later stages. */
	if (ENV_INITIAL_STAGE && !force_ro && !region_device_sz(&ro.rdev))
		cbfs_get_boot_device(true);

	if (!force_ro) {
		const struct cbfs_boot_device *rw = vboot_get_cbfs_boot_device();
		/* This will return NULL if vboot isn't enabled, didn't run yet or decided to
		   boot into recovery mode. */
		if (rw)
			return rw;
	}

	/* In rare cases post-RAM stages may run this before cbmem_initialize(), so we can't
	   lock in the result of find_mcache() on the first try and should keep trying every
	   time until an mcache is found. */
	cbfs_boot_device_find_mcache(&ro, CBMEM_ID_CBFS_RO_MCACHE);

	if (region_device_sz(&ro.rdev))
		return &ro;

	if (fmap_locate_area_as_rdev("COREBOOT", &ro.rdev))
		die("Cannot locate primary CBFS");

	if (ENV_INITIAL_STAGE) {
		cb_err_t err = cbfs_init_boot_device(&ro, metadata_hash_get());
		if (err == CB_CBFS_HASH_MISMATCH)
			die("RO CBFS metadata hash verification failure");
		else if (CONFIG(TOCTOU_SAFETY) && err == CB_CBFS_CACHE_FULL)
			die("RO mcache overflow breaks TOCTOU safety!\n");
		else if (err && err != CB_CBFS_CACHE_FULL)
			die("RO CBFS initialization error: %d", err);
	}

	return &ro;
}

#if !CONFIG(NO_CBFS_MCACHE)
static void mcache_to_cbmem(const struct cbfs_boot_device *cbd, u32 cbmem_id)
{
	if (!cbd)
		return;

	size_t real_size = cbfs_mcache_real_size(cbd->mcache, cbd->mcache_size);
	void *cbmem_mcache = cbmem_add(cbmem_id, real_size);
	if (!cbmem_mcache) {
		printk(BIOS_ERR, "ERROR: Cannot allocate CBMEM mcache %#x (%#zx bytes)!\n",
		       cbmem_id, real_size);
		return;
	}
	memcpy(cbmem_mcache, cbd->mcache, real_size);
}

static void cbfs_mcache_migrate(int unused)
{
	mcache_to_cbmem(vboot_get_cbfs_boot_device(), CBMEM_ID_CBFS_RW_MCACHE);
	mcache_to_cbmem(cbfs_get_boot_device(true), CBMEM_ID_CBFS_RO_MCACHE);
}
ROMSTAGE_CBMEM_INIT_HOOK(cbfs_mcache_migrate)
#endif

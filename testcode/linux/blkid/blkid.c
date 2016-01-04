#include<stdio.h>
#include<stdlib.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <errno.h>
#define FAT12_MAX                       0xff4
#define FAT16_MAX                       0xfff4
#define FAT32_MAX                       0x0ffffff6

#define FAT_ATTR_VOLUME_ID              0x08
#define FAT_ATTR_DIR                    0x10
#define FAT_ATTR_LONG_NAME              0x0f
#define FAT_ATTR_MASK                   0x3f
#define FAT_ENTRY_FREE                  0xe5

#define uint8_t unsigned char
#define uint64_t unsigned long long int
#define uint16_t unsigned short int
#define uint32_t unsigned  int

#define SB_BUFFER_SIZE				0x11000
#define SEEK_BUFFER_SIZE			0x10000
#define VOLUME_ID_VERSION               48

#define VOLUME_ID_LABEL_SIZE            64
#define VOLUME_ID_UUID_SIZE             36
#define VOLUME_ID_FORMAT_SIZE           32
#define VOLUME_ID_PARTITIONS_MAX        256

#define dbg(...) printf(__VA_ARGS__)

struct vfat_super_block {
        uint8_t         boot_jump[3];
        uint8_t         sysid[8];
        uint16_t        sector_size_bytes;
        uint8_t         sectors_per_cluster;
        uint16_t        reserved_sct;
        uint8_t         fats;
        uint16_t        dir_entries;
        uint16_t        sectors;
        uint8_t         media;
        uint16_t        fat_length;
        uint16_t        secs_track;
        uint16_t        heads;
        uint32_t        hidden;
        uint32_t        total_sect;
        union {
                struct fat_super_block {
                        uint8_t         unknown[3];
                        uint8_t         serno[4];
                        uint8_t         label[11];
                        uint8_t         magic[8];
                        uint8_t         dummy2[192];
                        uint8_t         pmagic[2];
                } fat;
                struct fat32_super_block {
                        uint32_t        fat32_length;
                        uint16_t        flags;
                        uint8_t         version[2];
                        uint32_t        root_cluster;
                        uint16_t        insfo_sector;
                        uint16_t        backup_boot;
                        uint16_t        reserved2[6];
                        uint8_t         unknown[3];
                        uint8_t         serno[4];
                        uint8_t         label[11];
                        uint8_t         magic[8];
                        uint8_t         dummy2[164];
                        uint8_t         pmagic[2];
                }  fat32;
        } type;
} ;
#define le16_to_cpu(x) (x)
#define le32_to_cpu(x) (x)
#define le64_to_cpu(x) (x)
struct vfat_dir_entry {
        uint8_t         name[11];
        uint8_t         attr;
        uint16_t        time_creat;
        uint16_t        date_creat;
        uint16_t        time_acc;
        uint16_t        date_acc;
        uint16_t        cluster_high;
        uint16_t        time_write;
        uint16_t        date_write;
        uint16_t        cluster_low;
        uint32_t        size;
} PACKED;
struct volume_id {
        int             fd;
//      int             fd_close:1;
        int             error;
        size_t          sbbuf_len;
        size_t          seekbuf_len;
        uint8_t         *sbbuf;
        uint8_t         *seekbuf;
        uint64_t        seekbuf_off;
//      uint8_t         label_raw[VOLUME_ID_LABEL_SIZE];
//      size_t          label_raw_len;
        char            label[VOLUME_ID_LABEL_SIZE+1];
//      uint8_t         uuid_raw[VOLUME_ID_UUID_SIZE];
//      size_t          uuid_raw_len;
        /* uuid is stored in ASCII (not binary) form here: */
        char            uuid[VOLUME_ID_UUID_SIZE+1];
//      char            type_version[VOLUME_ID_FORMAT_SIZE];
//      smallint        usage_id;
//      const char      *usage;

};


ssize_t safe_read(int fd, void *buf, size_t count)
{
        ssize_t n;


        do {
                n = read(fd, buf, count);
        } while (n < 0 && errno == EINTR);

        return n;
}

ssize_t full_read(int fd, void *buf, size_t len)
{
        ssize_t cc;
        ssize_t total;

        total = 0;

        while (len) {
                cc = safe_read(fd, buf, len);

                if (cc < 0) {
                        if (total) {
                                /* we already have some! */
                                /* user can do another read to know the error code */
                                return total;
                        }
                        return cc; /* read() returns -1 on failure. */
                }
                if (cc == 0)
                        break;
                buf = ((char *)buf) + cc;
                total += cc;
                len -= cc;
        }

        return total;
}

void*  xrealloc(void *ptr, size_t size)
{
        ptr = realloc(ptr, size);
        if (ptr == NULL && size != 0)
                printf("1111111111111111\n");
        return ptr;
}

static uint8_t *get_attr_volume_id(struct vfat_dir_entry *dir, int count)
{
        for (;--count >= 0; dir++) {
                /* end marker */
                if (dir->name[0] == 0x00) {
                        dbg("end of dir");
                        break;
                }

                /* empty entry */
                if (dir->name[0] == FAT_ENTRY_FREE)
                        continue;

                /* long name */
                if ((dir->attr & FAT_ATTR_MASK) == FAT_ATTR_LONG_NAME)
                        continue;

                if ((dir->attr & (FAT_ATTR_VOLUME_ID | FAT_ATTR_DIR)) == FAT_ATTR_VOLUME_ID) {
                        /* labels do not have file data */
                        if (dir->cluster_high != 0 || dir->cluster_low != 0)
                                continue;

                        dbg("found ATTR_VOLUME_ID id in root dir");
                        return dir->name;
                }

                dbg("skip dir entry");
        }

        return NULL;
}

void volume_id_free_buffer(struct volume_id *id)
{
        free(id->sbbuf);
        id->sbbuf = NULL;
        id->sbbuf_len = 0;
        free(id->seekbuf);
        id->seekbuf = NULL;
        id->seekbuf_len = 0;
        id->seekbuf_off = 0; /* paranoia */
}

void *volume_id_get_buffer(struct volume_id *id, uint64_t off, size_t len)
{
        uint8_t *dst;
        unsigned small_off;
        ssize_t read_len;

        dbg("1get buffer off 0x%llx(%llu), len 0x%zx",
                (unsigned long long) off, (unsigned long long) off, len);

        /* check if requested area fits in superblock buffer */
        if (off + len <= SB_BUFFER_SIZE
         /* && off <= SB_BUFFER_SIZE - want this paranoid overflow check? */
        ) {
                if (id->sbbuf == NULL) {
                        id->sbbuf = malloc(SB_BUFFER_SIZE);
			memset(id->sbbuf,0,SB_BUFFER_SIZE);
                }
                small_off = off;
                dst = id->sbbuf;

                /* check if we need to read */
                len += off;
                if (len <= id->sbbuf_len)
                        goto ret; /* we already have it */

                dbg("read sbbuf len:0x%x", (unsigned) len);
                id->sbbuf_len = len;
                off = 0;
                goto do_read;
        }

	if (len > SEEK_BUFFER_SIZE) {
                dbg("seek buffer too small %d", SEEK_BUFFER_SIZE);
                return NULL;
        }
        dst = id->seekbuf;

        /* check if we need to read */
        if ((off >= id->seekbuf_off)
         && ((off + len) <= (id->seekbuf_off + id->seekbuf_len))
        ) {
                small_off = off - id->seekbuf_off; /* can't overflow */
                goto ret; /* we already have it */
        }

        id->seekbuf_off = off;
        id->seekbuf_len = len;
        id->seekbuf = xrealloc(id->seekbuf, len);
        small_off = 0;
        dst = id->seekbuf;
        dbg("read seekbuf off:0x%llx len:0x%zx",
                                (unsigned long long) off, len);
 do_read:

	if (lseek(id->fd, off, SEEK_SET) != off) {
                dbg("seek(0x%llx) failed", (unsigned long long) off);
                goto err;
        }
        read_len = full_read(id->fd, dst, len);
        if (read_len != len) {
                dbg("requested 0x%x bytes, got 0x%x bytes",
                                (unsigned) len, (unsigned) read_len);
 err:
                /* No filesystem can be this tiny. It's most likely
                 * non-associated loop device, empty drive and so on.
                 * Flag it, making it possible to short circuit future
                 * accesses. Rationale:
                 * users complained of slow blkid due to empty floppy drives.
                 */
                if (off < 64*1024)
                        id->error = 1;
                /* id->seekbuf_len or id->sbbuf_len is wrong now! Fixing. */
                volume_id_free_buffer(id);
                return NULL;
        }
 ret:
	printf("wq%d %d\n",dst,small_off);
        return dst + small_off;
}

int  volume_id_probe_vfat(struct volume_id *id )
{
#define fat_partition_off ((uint64_t)0)
	struct vfat_super_block *vs;
	struct vfat_dir_entry *dir;
	uint16_t sector_size_bytes;
	uint16_t dir_entries;
	uint32_t sect_count;
	uint16_t reserved_sct;
	uint32_t fat_size_sct;
	uint32_t root_cluster;
	uint32_t dir_size_sct;
	uint32_t cluster_count;
	uint64_t root_start_off;
	uint32_t start_data_sct;
	uint8_t *buf;
	uint32_t buf_size;
	uint8_t *label = NULL;
	uint32_t next_cluster;
	int maxloop;

	dbg("probing at offset 0x%llx", (unsigned long long) fat_partition_off);

	vs = volume_id_get_buffer(id, fat_partition_off, 0x200);
	if (vs == NULL)
	{
		printf("2222222222");
		return -1;
	}

	/* believe only that's fat, don't trust the version
	 * the cluster_count will tell us
	 */
	memcpy(vs->type.fat32.magic, "FAT32   ", 8);

	if (memcmp(vs->sysid, "NTFS", 4) == 0)
		return -1;

	if (memcmp(vs->type.fat32.magic, "MSWIN", 5) == 0)
		goto valid;

	if (memcmp(vs->type.fat32.magic, "FAT32   ", 8) == 0)
		goto valid;

	if (memcmp(vs->type.fat.magic, "FAT16   ", 8) == 0)
		goto valid;

	if (memcmp(vs->type.fat.magic, "MSDOS", 5) == 0)
		goto valid;

	if (memcmp(vs->type.fat.magic, "FAT12   ", 8) == 0)
		goto valid;

	
	/*
	 * There are old floppies out there without a magic, so we check
	 * for well known values and guess if it's a fat volume
	 */

	/* boot jump address check */
	if ((vs->boot_jump[0] != 0xeb || vs->boot_jump[2] != 0x90)
	 && vs->boot_jump[0] != 0xe9
	) {
		return -1;
	}

	/* heads check */
	if (vs->heads == 0)
		return -1;

	/* cluster size check */
	if (vs->sectors_per_cluster == 0
	 || (vs->sectors_per_cluster & (vs->sectors_per_cluster-1))
	) {
		return -1;
	}

	/* media check */
	if (vs->media < 0xf8 && vs->media != 0xf0)
		return -1;

	/* fat count*/
	if (vs->fats != 2)
		return -1;

 valid:
printf("333333333333333333");
	printf("qw%d\n,",vs->sector_size_bytes);
	sleep(1);
	/* sector size check */
	sector_size_bytes = le16_to_cpu(vs->sector_size_bytes);
	if (sector_size_bytes != 0x200 && sector_size_bytes != 0x400
	 && sector_size_bytes != 0x800 && sector_size_bytes != 0x1000
	) {
		return -1;
	}

	dbg("sector_size_bytes 0x%x", sector_size_bytes);
	dbg("sectors_per_cluster 0x%x", vs->sectors_per_cluster);

	reserved_sct = le16_to_cpu(vs->reserved_sct);
	dbg("reserved_sct 0x%x", reserved_sct);

	sect_count = le16_to_cpu(vs->sectors);
	if (sect_count == 0)
		sect_count = le32_to_cpu(vs->total_sect);
	dbg("sect_count 0x%x", sect_count);

	fat_size_sct = le16_to_cpu(vs->fat_length);
	if (fat_size_sct == 0)
		fat_size_sct = le32_to_cpu(vs->type.fat32.fat32_length);
	fat_size_sct *= vs->fats;
	dbg("fat_size_sct 0x%x", fat_size_sct);

	dir_entries = le16_to_cpu(vs->dir_entries);
	dir_size_sct = ((dir_entries * sizeof(struct vfat_dir_entry)) +
			(sector_size_bytes-1)) / sector_size_bytes;
	dbg("dir_size_sct 0x%x", dir_size_sct);

	cluster_count = sect_count - (reserved_sct + fat_size_sct + dir_size_sct);
	cluster_count /= vs->sectors_per_cluster;
	dbg("cluster_count 0x%x", cluster_count);


	if (cluster_count >= FAT16_MAX)
		goto fat32;

	

 fat32:
	/* FAT32 root dir is a cluster chain like any other directory */
	buf_size = vs->sectors_per_cluster * sector_size_bytes;
	root_cluster = le32_to_cpu(vs->type.fat32.root_cluster);
	start_data_sct = reserved_sct + fat_size_sct;

	next_cluster = root_cluster;
	maxloop = 100;
	while (--maxloop) {
		uint64_t next_off_sct;
		uint64_t next_off;
		uint64_t fat_entry_off;
		int count;

		dbg("next_cluster 0x%x", (unsigned)next_cluster);
		next_off_sct = (uint64_t)(next_cluster - 2) * vs->sectors_per_cluster;
		next_off = (start_data_sct + next_off_sct) * sector_size_bytes;
		dbg("cluster offset 0x%llx", (unsigned long long) next_off);

		/* get cluster */
		buf = volume_id_get_buffer(id, fat_partition_off + next_off, buf_size);
		if (buf == NULL)
			goto ret;

		dir = (struct vfat_dir_entry*) buf;
		count = buf_size / sizeof(struct vfat_dir_entry);
		dbg("expected entries 0x%x", count);

		label = get_attr_volume_id(dir, count);
		if (label)
			break;

		
	}
	if (maxloop == 0)
		dbg("reached maximum follow count of root cluster chain, give up");

	vs = volume_id_get_buffer(id, fat_partition_off, 0x200);
	if (vs == NULL)
		return -1;


	//volume_id_set_uuid(id, vs->type.fat32.serno, UUID_DOS);

 ret:
//	volume_id_set_usage(id, VOLUME_ID_FILESYSTEM);
	//IF_FEATURE_BLKID_TYPE(id->type = "vfat";)

	return 0;
}

int main(int argc, char** argv)
{
	int fd = open(argv[1], O_RDONLY);
        struct volume_id *id;
          

      
        id = malloc(sizeof(struct volume_id));
	memset(id,0,sizeof(struct volume_id));
        id->fd = fd;
	
	volume_id_probe_vfat(id);

	printf("==========%s\n",id->label);
        return fd;

}

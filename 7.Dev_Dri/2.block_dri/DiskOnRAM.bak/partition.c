#include <linux/string.h>

#include "partition.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

#define SECTOR_SIZE 512
#define MBR_SIZE SECTOR_SIZE
#define MBR_DISK_SIGNATURE_OFFSET 440
#define MBR_DISK_SIGNATURE_SIZE 4
#define PARTITION_TABLE_OFFSET 446
#define PARTITION_ENTRY_SIZE 16 // sizeof(PartEntry)
#define PARTITION_TABLE_SIZE 64 // sizeof(PartTable)
#define MBR_SIGNATURE_OFFSET 510
#define MBR_SIGNATURE_SIZE 2
#define MBR_SIGNATURE 0xAA55
#define BR_SIZE SECTOR_SIZE
#define BR_SIGNATURE_OFFSET 510
#define BR_SIGNATURE_SIZE 2
#define BR_SIGNATURE 0xAA55
#define MAX_NUM_PTBL 4

#define LINUX_PART 0x83
#define LINUX_EXTEND 0x05
#define START_SECT 1
#define PART1_SIZE 128*1024 //Bytes
#define PART1_SECT (PART1_SIZE)/SECTOR_SIZE
//#define CHS

typedef struct{
	unsigned char boot_type; // 0x00 - Inactive; 0x80 - Active (Bootable)
	unsigned char start_head;
	unsigned char start_sec:6;
	unsigned char start_cyl_hi:2;
	unsigned char start_cyl;
	unsigned char part_type;
	unsigned char end_head;
	unsigned char end_sec:6;
	unsigned char end_cyl_hi:2;
	unsigned char end_cyl;
	unsigned int abs_start_sec;
	unsigned int sec_in_part;
} PartEntry;

typedef PartEntry PartTable[MAX_NUM_PTBL];
static PartTable def_part_table =
{
    //C: 0-1023 10bits
    //H: 0-255  8 bits
    //S: 1-63   6 bits
	{
		boot_type: 0x00,
#ifdef CHS
		start_head: 0x00,
		start_sec: 0x1,
		start_cyl: 0x00,
#endif
		part_type: LINUX_PART, // echo l | fdisk /dev/rb
#ifdef CHS
		end_head: 0x32,
		end_sec: 0x20,
		end_cyl: 0x00,
#endif
        abs_start_sec: START_SECT,
		sec_in_part: PART1_SECT
	},
#if 0
    {
		boot_type: 0x00,
#ifdef CHS
		start_head: 0x00,
		start_sec: 0x1,
		start_cyl: 0x0A, // extended partition start cylinder (BR location)
#endif
		part_type: 0x05,
#ifdef CHS
		end_head: 0x00,
		end_sec: 0x20,
		end_cyl: 0x13,
#endif
		abs_start_sec: 0x00000140,
		sec_in_part: 0x00000140
	},
	{
		boot_type: 0x00,
#ifdef CHS
		start_head: 0x00,
		start_sec: 0x1,
		start_cyl: 0x14,
#endif
        part_type: 0x83,
#ifdef CHS
        end_head: 0x00,
		end_sec: 0x20,
		end_cyl: 0x1F,
#endif
        abs_start_sec: 0x00000280,
		sec_in_part: 0x00000180
	},
#endif
	{
	}
};
//static unsigned int def_log_part_br_cyl[] = {0x0A, 0x0E, 0x12};
#if 0
static const PartTable def_log_part_table[] =
{
	{
		{
			boot_type: 0x00,
#ifdef CHS 
            start_head: 0x00,
			start_sec: 0x2,
			start_cyl: 0x0A,
#endif
			part_type: 0x83,
#ifdef CHS 
			end_head: 0x00,
			end_sec: 0x20,
			end_cyl: 0x0D,
#endif
			abs_start_sec: 0x00000001,
			sec_in_part: 0x0000007F
		},
		{
			boot_type: 0x00,
#ifdef CHS 
			start_head: 0x00,
			start_sec: 0x1,
			start_cyl: 0x0E,
#endif
			part_type: 0x05,
#ifdef CHS 
			end_head: 0x00,
			end_sec: 0x20,
			end_cyl: 0x11,
#endif
			abs_start_sec: 0x00000080,
			sec_in_part: 0x00000080
		},
	},
	{
		{
			boot_type: 0x00,
#ifdef CHS 
			start_head: 0x00,
			start_sec: 0x2,
			start_cyl: 0x0E,
#endif
			part_type: 0x83,
#ifdef CHS 
			end_head: 0x00,
			end_sec: 0x20,
			end_cyl: 0x11,
#endif
			abs_start_sec: 0x00000001,
			sec_in_part: 0x0000007F
		},
		{
			boot_type: 0x00,
#ifdef CHS 
			start_head: 0x00,
			start_sec: 0x1,
			start_cyl: 0x12,
#endif
			part_type: 0x05,
#ifdef CHS 
			end_head: 0x00,
			end_sec: 0x20,
			end_cyl: 0x13,
#endif
			abs_start_sec: 0x00000100,
			sec_in_part: 0x00000040
		},
	},
	{
		{
			boot_type: 0x00,
#ifdef CHS 
			start_head: 0x00,
			start_sec: 0x2,
			start_cyl: 0x12,
#endif
			part_type: 0x83,
#ifdef CHS 
			end_head: 0x00,
			end_sec: 0x20,
			end_cyl: 0x13,
#endif
			abs_start_sec: 0x00000001,
			sec_in_part: 0x0000003F
		},
	}
};
#endif
static void copy_br_ptbl(u8 *disk, int start_cylinder, const PartTable *part_table)
{
	memcpy(disk + PARTITION_TABLE_OFFSET, &def_part_table, PARTITION_TABLE_SIZE);
#if 0
    
    disk += (start_cylinder * 32 /* sectors / cyl */ * SECTOR_SIZE);
	memset(disk, 0x0, BR_SIZE);
	memcpy(disk + PARTITION_TABLE_OFFSET, part_table,
		PARTITION_TABLE_SIZE);
	*(unsigned short *)(disk + BR_SIGNATURE_OFFSET) = BR_SIGNATURE;
#endif
}

void copy_mbr_n_br(u8 *disk)
{
    u8 *disk_start = disk;
	memset(disk, 0x0, MBR_SIZE);
	*(unsigned long *)(disk + MBR_DISK_SIGNATURE_OFFSET) = 0xbadc0ffe;//0x36E5756D;
    copy_br_ptbl(disk,0,NULL);
	*(unsigned short *)(disk_start + MBR_SIGNATURE_OFFSET) = MBR_SIGNATURE;
}
#if 0
void copy_mbr_n_br(u8 *disk)
{
	int i;

	copy_mbr(disk);
	for (i = 0; i < ARRAY_SIZE(def_log_part_table); i++)
	{
		copy_br(disk, def_log_part_br_cyl[i], &def_log_part_table[i]);
	}
}
#endif

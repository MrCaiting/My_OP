#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#define BOOTBLOCK_RESERVED  52
#define DIRECTORY_ENT       64

#include "lib.h"
#include "types.h"

typedef struct boot_block{
  uint32_t num_directory_entires;
  uint32_t num_inodes;
  uint32_t num_data_blocks;
  uint8_t  reserved[BOOTBLOCK_RESERVED];
  dentry_block_t directory_entries[DIRECTORY_ENT];
}boot_block_t;

extern void init_file_system (uint32_t address);
extern int32_t file_open(const uint8_t* filename);
extern int32_t file_close(const uint8_t* filename);
extern int32_t file_write(int32_t fd, void8 buf, int32_t nbytes);
extern int32_t file_read(int32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);
extern int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

extern int32_t directory_open(void);
extern int32_t directory_write(void);
extern int32_t directory_close(void;
extern int32_t directory_read(int32_t fd, void* buf, int32_t nbytes);
extern int32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry);
extern int32_t read_dentry_by_index (uint32_t index, dentry_t* dentry);

#endif

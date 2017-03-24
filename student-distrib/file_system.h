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

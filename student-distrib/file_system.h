#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "lib.h"
#include "types.h"

typedef struct boot_block{
  uint32_t num_directory_entires;
  uint32_t num_inodes;
  uint32_t num_data_blocks;
  
}

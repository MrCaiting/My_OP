#include "file_system.h"

static boot_block_t* bootpoint;
static inode_t* first_inode;
static data_block_t* data;

void init_file_system (uint32_t address){
  uint32_t num_of_inodes;

  bootpoint = (boot_block_t*) address;
  num_of_inodes = bootpoint->num_inodes;

  first_inode = (inode_t*) (bootpoint+1);
  data = (data_block_t*) (boot_block_t + 1 + num_of_inodes);
}


int32_t file_open(const uint8_t* filename){
  return 0;
}

/*
 * Read only filesystem, this function is basically useless
 */
int32_t file_write(int32_t fd, void8 buf, int32_t nbytes){
  return -1;
}

int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length){

}

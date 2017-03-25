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
  int32_t n;
  int32_t data_length;
  int32_t data_copied;
  int32_t data_need_read;
  int32_t data_bl_start;
  int32_t index = 0;
  uint32_t current_block;
  inode_t* inode_copy;
  uint8_t* byte_copy;

  inode_copy = (first_inode + inode);
  data_length = (first_inode + inode)->inode_len;
  data_length -= offset;      // Include the offset and get the actual length of data

  // If there is no data to be read (EOF has been reached)
  if (data_length <= 0){
    return 0;
  }

  // If the inode value is invalid or the buffer is not ready
  if (inode > bootpoint->num_inodes || !buf){
    return -1;
  }

  if (data_length < length)   // If the length of the data remain is smaller than the requested length
    data_need_read = data_length;   // we only read the available length
  }
  else{
    data_need_read = length;
  }

  data_copied = 0;
  while (data_need_read > 0){
    current_block = offset / DATA_B_SIZE;

    byte_copy = (uint8_t*) &data[inode_copy->in_d_block_num[current_block]] + (offset % DATA_B_SIZE);

    n = (length > 4096 - (offset % 4096))?(4096 - (offset % 4096))):length;
    memcpy(buf, byte_copy, n);

    data_need_read -= n;
    data_copied += n;
    buf += n;
    offset += n;
    }
    return data_copied;
  }
}

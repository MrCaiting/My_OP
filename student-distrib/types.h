/* types.h - Defines to use the familiar explicitly-sized types in this
 * OS (uint32_t, int8_t, etc.).  This is necessary because we don't want
 * to include <stdint.h> when building this OS
 * vim:ts=4 noexpandtab
 */

#ifndef _TYPES_H
#define _TYPES_H

#define NULL 0
/* Newly added constants */
#define NAME_SIZE       32     // length of the name is up to 32 characters
#define DEN_RESERVE     24     // dentry reserved block is 24 byte
#define DATA_B_SIZE   4096     // each data block is 4 KB = 1024 byte (8 bit) * 4
#define INODE_D_BLOCK 1023     // number of data_block_num in a inode (1024-1) due to first length entry

#ifndef ASM

/* Types defined here just like in <stdint.h> */
typedef int int32_t;
typedef unsigned int uint32_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef char int8_t;
typedef unsigned char uint8_t;

/* Newly added types for file system */

typedef struct dentry_block{
  uint8_t file_name[NAME_SIZE];     // used uint8_t since the typedef of unsigned char defined above
  uint32_t file_type;
  uint32_t inode_number;
  uint8_t dentry_reserved[DEN_RESERVE];
}dentry_t;

typedef struct data_block{
  uint8_t data[DATA_B_SIZE];
}data_block_t;

typedef struct inode{
  uint32_t inode_len;
  uint32_t in_d_block_num[INODE_D_BLOCK];
}inode_t;



#endif /* ASM */

#endif /* _TYPES_H */

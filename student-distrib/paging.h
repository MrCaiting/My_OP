/*
paging.h
*/
#ifndef _PAGING_H
#define _PAGING_H
#ifndef ASM
#include "lib.h"
#include "types.h"

/*start to set up kernel and video paging*/
extern void kernel_video_paging(uint32_t ker_addr, uint32_t vid_addr);

#endif
#endif

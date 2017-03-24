/*
paging.c
Description: initialize and set up page directory and page table
             for both video memory and kernel memory.
Created by Shengkun Cui scui8
*/
#include "paging.h"
#define PAGE_SIZE 0x1000
#define VIDEO 0xB8000
#define PD_ADDR_BITS 22
#define PT_ADDR_BITS 12
#define ADDR_MASK 0X3FF
#define ENB_PRE_USR_RW 0x7
#define DISABLE 0x0
#define LAREG_PG 0x80
#define ENABLE 1
#define PAGE_ENTRIES 1024

static uint32_t page_dic[PAGE_ENTRIES]__attribute__((aligned(PAGE_SIZE)));
static uint32_t page_tab[PAGE_ENTRIES]__attribute__((aligned(PAGE_SIZE)));

// assign_pg_tab_linear entry by calculating the address offest
static void assign_pg_tab_linear(uint32_t addr);

// turn on paging using asm helper function
static void enable_asm(uint32_t pd);

/*initialize PD and PT entries*/
static void paging_clear_init(void);

/*turn on paging mode*/
static void enable_paging(void);

/* set up PD*/
static void insert_pg_dic_linear(uint32_t addr, uint32_t pt_addr, int four_mb);

/*
void paging_clear_init
Description: initialize all entries in page table and page directory to unpresent
INPUT: none
OUTPUT: none
*/
void paging_clear_init(void){
    int idx;
    for(idx = 0; idx<PAGE_ENTRIES; idx++){
        // initialized all entries to not present, buth the table and the directpry
        page_dic[idx]= DISABLE;
        page_tab[idx] = DISABLE;
    }
    return;
}

/*
 void kernel_video_paging
Description: call by kernel.c, start setting paging
INPUT: linear address of kernel memory and video memory
OUTPUT: none
*/
 void kernel_video_paging(uint32_t ker_addr, uint32_t vid_addr){
    paging_clear_init();
    insert_pg_dic_linear(ker_addr,DISABLE,ENABLE);  // for 4MB mode, kernel memory
    insert_pg_dic_linear(vid_addr,(uint32_t)page_tab,DISABLE); // for 4kb mode, video memory
    enable_paging(); // turn on paging mode
}

/*
void insert_pg_dic_linear
Description: set up page directory for video and kernel memory
INPUT: linear address of kernel memory and video memory
OUTPUT: none
*/

void insert_pg_dic_linear(uint32_t addr, uint32_t pt_addr, int four_mb){

    uint32_t pd_idx = addr>> PD_ADDR_BITS & ADDR_MASK; // calculate page directory index
    if(four_mb){
        page_dic[pd_idx] = addr | ENB_PRE_USR_RW | LAREG_PG; // for 4 mb mode, set PDE
        return;
    }
    else{
        page_dic[pd_idx] = pt_addr | ENB_PRE_USR_RW; // for 4kb mode, set PDE
        assign_pg_tab_linear(addr);
        return;
    }
}

/*
void assign_pg_tab_linear
Description: set up page table for both kernel and video memory
INPUT: linear address of video memory
OUTPUT: none
*/

void assign_pg_tab_linear(uint32_t addr){
    int pt_idx = (addr >> PT_ADDR_BITS) & ADDR_MASK;    // calculate page table index
    page_tab[pt_idx] = page_tab[pt_idx] | addr | ENB_PRE_USR_RW; // set up page table entry(PTE) for corresponding index
}

/*
void enable_paging
Description:  call enable_asm to open up paging mode
INPUT: none
OUTPUT: none
*/
void enable_paging(void){
    enable_asm((uint32_t)page_dic); // open up paging mode
}

/*
void enable_asm
Description: open up paging mode
INPUT: page directory address
OUTPUT: none
SIDEEFFECT: set up corresponding bits in CR0, CR3, CR4
NOTE: 0x00000010 for CR4, set PSE, enable 4MB page mode
      0x80000001 for CR0, set PG, enable paging mode
                 for CR0, set PE, enable protexted mode (segmentation)
*/

void enable_asm(uint32_t pd)
{
    asm         ("              \n\
    movl %0,%%eax               \n\
    movl %%eax,%%cr3            \n\
    movl %%cr4,%%eax            \n\
    orl $0x00000010,%%eax       \n\
    movl %%eax,%%cr4            \n\
    movl %%cr0,%%eax            \n\
    orl $0x80000001,%%eax       \n\
    movl %%eax,%%cr0            \n\
    "
                 :
                 : "g"(pd)
                 : "eax");
}

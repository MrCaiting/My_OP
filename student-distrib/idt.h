/*
* IDT header
* Provide functions to be used in kernel.c
* idt_entry_init: initialized IDT entries, fill the table
* idt_handler_init_intel: install intel exception handlers to function array
* idt_handler_init_pic: install pic exception handlers to function array
* Created on 03/12/2017 by Shengkun Cui, scui8
*/
#ifndef _IDT_H
#define _IDT_H
#include "idt_handlers.h"
#include "idt_asm.h"

// external function that will be used in the kernel.c function to
// initialized IDT table with handlers
extern void init_IDT(void);

#endif

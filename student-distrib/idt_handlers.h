/*
* IDT handler headers
* This header contains interrupt function header that will be used
* in this checkpoint, the basic 0-21 exception handlers, keyboard, rtc
* handlers, the function will be called in idt_asm.c
* Created on 03/12/2017 by Shengkun Cui, scui8
*/
#ifndef _IDT_HANDLERS_H
#define _IDT_HANDLERS_H
#include "x86_desc.h"
#include "lib.h"
#include "debug.h"
#include "i8259.h"
#include "scancode_to_ascii.h"
#include "types.h"

// first 22 expections defined by intel, find function header in .c for details
extern void divide_by_zero(void);
extern void debugger(void);
extern void nmi(void);
extern void breakpoint(void);
extern void overflow(void);
extern void bounds(void);
extern void invalid_opcode(void);
extern void copro_not_ava(void);
extern void double_falt(void);
extern void cop_overrun(void);
extern void inv_tassk_ss(void);
extern void seg_not_pre(void);
extern void stack_falt(void);
extern void gen_pro_fal(void);
extern void page_falt(void);
extern void reserved(void);
extern void math_falt(void);
extern void align_check(void);
extern void mach_check(void);
extern void float_exp(void);
extern void virtual_exp(void);
extern void con_pro_exp(void);
extern void default_hand(void);
extern void sys_call(void);

// pic interrupt handlers for keyboard and rtc, find function header in .c for details
extern void keyboard(void);
extern void rtc(void);
#endif

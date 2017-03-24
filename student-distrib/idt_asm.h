/*
* Interrupt/exception handler assmebly wrapper header
* Created on 03/12/2017 by Shengkun Cui, scui8
*/
#ifndef _IDT_ASM_H
#define _IDT_ASM_H
#ifndef ASM
#include "idt_handlers.h"

//////////////////////////////////////////////////////////////////
// Assembly wrapper label pointer used in idt.c to populate array
// use uint32_t since the functions are labels in the assembly code
extern uint32_t divide_by_zero_asm_irq;
extern uint32_t debugger_asm_irq;
extern uint32_t nmi_asm_irq;
extern uint32_t breakpoint_asm_irq;
extern uint32_t overflow_asm_irq;
extern uint32_t bounds_asm_irq;
extern uint32_t invalid_opcode_asm_irq;
extern uint32_t copro_not_ava_asm_irq;
extern uint32_t double_falt_asm_irq;
extern uint32_t cop_overrun_asm_irq;
extern uint32_t inv_tassk_ss_asm_irq;
extern uint32_t seg_not_pre_asm_irq;
extern uint32_t stack_falt_asm_irq;
extern uint32_t gen_pro_fal_asm_irq;
extern uint32_t page_falt_asm_irq;
extern uint32_t reserved_asm_irq;
extern uint32_t math_falt_asm_irq;
extern uint32_t align_check_asm_irq;
extern uint32_t mach_check_asm_irq;
extern uint32_t float_exp_asm_irq;
extern uint32_t virtual_exp_asm_irq;
extern uint32_t con_pro_exp_asm_irq;
extern uint32_t default_hand_asm_irq;
extern uint32_t sys_call_asm_irq;

extern uint32_t keyboard_asm_irq;
extern uint32_t rtc_asm_irq;
////////////////////////////////////////////////////////////////
#endif
#endif

#define ASM 1
#include "idt_asm.h"
    # global section for exception handler asm wrapper
.global divide_by_zero_asm_irq, debugger_asm_irq
.global nmi_asm_irq, breakpoint_asm_irq, overflow_asm_irq
.global bounds_asm_irq, invalid_opcode_asm_irq, copro_not_ava_asm_irq
.global double_falt_asm_irq, cop_overrun_asm_irq ,inv_tassk_ss_asm_irq
.global seg_not_pre_asm_irq,stack_falt_asm_irq, gen_pro_fal_asm_irq
.global page_falt_asm_irq,reserved_asm_irq, math_falt_asm_irq
.global align_check_asm_irq,mach_check_asm_irq, float_exp_asm_irq
.global virtual_exp_asm_irq,con_pro_exp_asm_irq, default_hand_asm_irq
.global sys_call_asm_irq

    # global section for interrupt handler asm wrapper
.global keyboard_asm_irq, rtc_asm_irq

    #   Division by zero asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
divide_by_zero_asm_irq:
    pushal
    call divide_by_zero
    popal
    iret

    #   Debugger Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
debugger_asm_irq:
    pushal
    call debugger
    popal
    iret

    #   NMI Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
nmi_asm_irq:
    pushal
    call nmi
    popal
    iret

    #   Break Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
breakpoint_asm_irq:
    pushal
    call breakpoint
    popal
    iret

    #   Overflow Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
overflow_asm_irq:
    pushal
    call overflow
    popal
    iret

    #   Out of Bounds Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
bounds_asm_irq:
    pushal
    call bounds
    popal
    iret

    #   Invalid Opcode Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
invalid_opcode_asm_irq:
    pushal
    call invalid_opcode
    popal
    iret

    #   Co-processor not avaliable Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
copro_not_ava_asm_irq:
    pushal
    call copro_not_ava
    popal
    iret

    #   Double Fault Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
    #   double fault has error code that we have to pop it off the stack to
    #   prevent overflow
double_falt_asm_irq:
    pushal
    call double_falt
    popal
    addl $4, %esp
    iret

    #   Co-processor Overrun Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
cop_overrun_asm_irq:
    pushal
    call cop_overrun
    popal
    iret

    #   Invalid TSS asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
    #   double fault has error code that we have to pop it off the stack to
    #   prevent overflow
inv_tassk_ss_asm_irq:
    pushal
    call inv_tassk_ss
    popal
    addl $4, %esp
    iret

    #   Segment not present asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
    #   double fault has error code that we have to pop it off the stack to
    #   prevent overflow
seg_not_pre_asm_irq:
    pushal
    call seg_not_pre
    popal
    addl $4, %esp
    iret

    #   Stack Fault asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
    #   double fault has error code that we have to pop it off the stack to
    #   prevent overflow
stack_falt_asm_irq:
    pushal
    call stack_falt
    popal
    addl $4, %esp
    iret

    #   General Protection Fault asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
    #   double fault has error code that we have to pop it off the stack to
    #   prevent overflow
gen_pro_fal_asm_irq:
    pushal
    call gen_pro_fal
    popal
    addl $4, %esp
    iret

    #   Page Fault asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
    #   double fault has error code that we have to pop it off the stack to
    #   prevent overflow
page_falt_asm_irq:
    pushal
    call page_falt
    popal
    addl $4, %esp
    iret

    #   Resereved handler asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
reserved_asm_irq:
    pushal
    call reserved
    popal
    iret

    #   Math fault handler asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
math_falt_asm_irq:
    pushal
    call math_falt
    popal
    iret

    #   Alignment Check Exception handler asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
align_check_asm_irq:
    pushal
    call align_check
    popal
    iret

    #   Machine Check Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
mach_check_asm_irq:
    pushal
    call mach_check
    popal
    iret

    #   Floating point fail Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
float_exp_asm_irq:
    pushal
    call float_exp
    popal
    iret

    #   Virtualization Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
virtual_exp_asm_irq:
    pushal
    call virtual_exp
    popal
    iret

    #   Co-processor overrun Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
con_pro_exp_asm_irq:
    pushal
    call con_pro_exp
    popal
    iret

    #   Default Exception asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
default_hand_asm_irq:
    pushal
    call default_hand
    popal
    iret

sys_call_asm_irq:
    pushal
    call sys_call
    popal
    iret

    #   keyboard interrupt handler asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
keyboard_asm_irq:
    pushal
    call keyboard
    popal
    iret

    #   rtc interrupt handler asm wrapper
    #   input none
    #   output none
    #   side effect: restore flags go back to program being interrupted
rtc_asm_irq:
    pushal
    call rtc
    popal
    iret

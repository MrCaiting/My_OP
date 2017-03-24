
/*
idt_handles.c
This file contains the interrupt handler implementations.
*/

/*
 * divide_by_zero
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */

 #define KEY_BOARD 0x60
 #define KEY_BOARD_IRQ 0x01
 #define NAN 0x0
 #define REG_C 0x0C
 #define RTC_CMD 0x70
 #define RTC_DATA 0x71
 #define RTC_IRQ 0x08
#include "idt_handlers.h"

void divide_by_zero(void){
    printf("Division by zero.\n");
    while(1);
}

/*
 * debugger
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void debugger(void){
    printf("Debugger.\n");
    while(1);
}

/*
 * nmi
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void nmi(void){
    printf("NMI.\n");
    while(1);
}

/*
 * breakpoint
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void breakpoint(void){
    printf("Break Point.\n");
    while(1);
}

/*
 * overflow
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void overflow(void){
    printf("Overflow.\n");
    while(1);
}

/*
 * bounds
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void bounds(void){
    printf("Bounds.\n");
    while(1);
}

/*
 * invalid_opcode
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void invalid_opcode(void){
    printf("Invalid Opcode.\n");
    while(1);
}

/*
 * copro_not_ava
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void copro_not_ava(void){
    printf("Coprocessor not available.\n");
    while(1);
}

/*
 * double_fault
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void double_falt(void){
    printf("Double falt, check handlers.\n");
    while(1);
}

/*
 * cop_overrun
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void cop_overrun(void){
    printf("Coprocessor Segment Overrun.\n");
    while(1);
}

/*
 * inv_task_ss
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void inv_tassk_ss(void){
    printf("Invalid Task State Segment.\n");
    while(1);
}

/*
 * seg_not_pre
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void seg_not_pre(void){
    printf("Segment not present.\n");
    while(1);
}

/*
 * stack_falt
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void stack_falt(void){
    printf("Stack falt.\n");
    while(1);
}

/*
 * gen_pro_fal
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void gen_pro_fal(void){
    printf("General protection fault\n");
    while(1);
}

/*
 * page_falt
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void page_falt(void){
    printf("Page Fault.\n");
    while(1);
}

/*
 * reserved
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void reserved(void){
    printf("Reserved.\n");
    while(1);
}

/*
 * math_falt
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void math_falt(void){
    printf("Math Fault.\n");
    while(1);
}

/*
 * align_check
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void align_check(void){
    printf("Alignment Check.\n");
    while(1);
}

/*
 * mach_check
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void mach_check(void){
    printf("Machine Check.\n");
    while(1);
}

/*
 * float_exp
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void float_exp(void){
    printf("Floating-Point Exception.\n");
    while(1);
}

/*
 * virtual_exp
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void virtual_exp(void){
    printf("Virtualization Exception.\n");
    while(1);
}

/*
 * con_pro_exp
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void con_pro_exp(void){
    printf("Control Protection Exception.\n");
    while(1);
}

/*
 * default_hand
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void default_hand(void){
    printf("Default Handler.\n");
    while(1);
}

/*
 * keyboard
 *   DESCRIPTION: handle exception, print out the exception name
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void keyboard(void){
    char inchar = inb(KEY_BOARD);
    char outchar;
    outchar = keyscan_to_ascii(inchar);

    // only print to screen for 0-9, a-z, A-Z, and some other characters
    if(outchar!=NAN)
        putc(outchar);
    send_eoi(KEY_BOARD_IRQ);
}

/*
 * rtc
 *   DESCRIPTION: receive RTC and flush the buffer
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 */
void rtc(void){
    // received RTC
    test_interrupts();

    // select register C and flush the buffer
    outb(REG_C,RTC_CMD);
    inb(RTC_DATA);
    send_eoi(RTC_IRQ);
}

void sys_call(void){
    printf("System Call!\n");
    while(1);
}

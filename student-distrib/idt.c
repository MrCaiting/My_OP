/*
* IDT Function body
* Function definitions, see function header for usage
* Created on 03/12/2017 by Shengkun Cui, scui8
*/
#include "idt.h"

// total interrupt entries
#define TOTAL_INT 256

// key board interrupt handler vector, default on irq1 master pic
#define KEY_BOARD_INT 33

// rtc interrupt handler vector, default on irq0 slave pic
#define RTC_INT 40

// mark the end point of defined intel exceptions, 22--31 are reserved but not
// defined on most of the web sources or in the references, 22--31 will be
// filled with default interrupt handlers
#define END_OF_INTEL_EXP_DEF 22

// mark the starting entry for interrupt, 0--31 are reserved expections
#define START_OF_INT 32

// boolean integers, Disable also describes DPL at 0
#define DISABLE 0
#define ENABLE 1

// user program privilege
#define USER_MODE 3

// entry size in IDT
#define ENTRY_SIZE 8

// system call entry x80
#define SYS_CALL 0x80

// function initialized the table entry
static void idt_entry_init(void);

// function that fills the table vector address
static void idt_handler_init_asm(void);

/*
 * idt_handler_init_intel
 *   DESCRIPTION: initialize intel exception handlers for the first 22 entries
 *                defined on http://wiki.osdev.org/ into the table entry
                  the unused entries for this checkpoint are filled with
                  default handlers
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: writes the handler pointer in idt_handlers.c into table
 *   NOTE : the number 0--21 in the function below is the array index, as well
 *          as the exception handler vector in the IDT, the 0--21 entries are
 *          used and defined by intel, 22--31 are reserved but defined so
 *          these entries has default interrupt handlers.
 */
void idt_handler_init_asm(void){
    uint32_t idx;

    // populates the first 22 entries in the table
     SET_IDT_ENTRY(idt[0],&divide_by_zero_asm_irq);
     SET_IDT_ENTRY(idt[1],&debugger_asm_irq);
     SET_IDT_ENTRY(idt[2],&nmi_asm_irq);
     SET_IDT_ENTRY(idt[3],&breakpoint_asm_irq);
     SET_IDT_ENTRY(idt[4],&overflow_asm_irq);
     SET_IDT_ENTRY(idt[5],&bounds_asm_irq);
     SET_IDT_ENTRY(idt[6],&invalid_opcode_asm_irq);
     SET_IDT_ENTRY(idt[7],&copro_not_ava_asm_irq);
     SET_IDT_ENTRY(idt[8],&double_falt_asm_irq);
     SET_IDT_ENTRY(idt[9],&cop_overrun_asm_irq);
     SET_IDT_ENTRY(idt[10],&inv_tassk_ss_asm_irq);
     SET_IDT_ENTRY(idt[11],&seg_not_pre_asm_irq);
     SET_IDT_ENTRY(idt[12],&stack_falt_asm_irq);
     SET_IDT_ENTRY(idt[13],&gen_pro_fal_asm_irq);
     SET_IDT_ENTRY(idt[14],&page_falt_asm_irq);
     SET_IDT_ENTRY(idt[15],&reserved_asm_irq);
     SET_IDT_ENTRY(idt[16],&math_falt_asm_irq);
     SET_IDT_ENTRY(idt[17],&align_check_asm_irq);
     SET_IDT_ENTRY(idt[18],&mach_check_asm_irq);
     SET_IDT_ENTRY(idt[19],&float_exp_asm_irq);
     SET_IDT_ENTRY(idt[20],&virtual_exp_asm_irq);
     SET_IDT_ENTRY(idt[21],&con_pro_exp_asm_irq);

    // set all the unused functions to default handler at this point
    for(idx = END_OF_INTEL_EXP_DEF; idx<TOTAL_INT;idx++){
        SET_IDT_ENTRY(idt[idx],&default_hand_asm_irq);
    }

    // put pic handlers into IDT
    SET_IDT_ENTRY(idt[KEY_BOARD_INT], &keyboard_asm_irq);
    SET_IDT_ENTRY(idt[RTC_INT], &rtc_asm_irq);

    // put system call into x80
    SET_IDT_ENTRY(idt[SYS_CALL], &sys_call_asm_irq);
}

/*
 * idt_handler_init_pic
 *   DESCRIPTION: initialize table entries with the given vector number
 *   INPUTS: vector number indicates table entry
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: initialize entries of the table, everything but the address
 */
 void idt_entry_init(){
     uint32_t vec_num;
     for(vec_num = 0; vec_num<TOTAL_INT;vec_num++){
         // the first 31 entries are set to type exception in filed reserved3 to 1
         if(vec_num<START_OF_INT){
             idt[vec_num].seg_selector = KERNEL_CS;
             idt[vec_num].reserved4 = DISABLE;
             idt[vec_num].reserved3 = ENABLE;
             idt[vec_num].reserved2 = ENABLE;
             idt[vec_num].reserved1 = ENABLE;
             idt[vec_num].size = ENABLE;
             idt[vec_num].reserved0 = DISABLE;
             idt[vec_num].dpl = DISABLE;
             idt[vec_num].present = ENABLE;
         }

         // the rest of the entries are set to type interrupt in filed reserved3 to 1
         else{
             idt[vec_num].seg_selector = KERNEL_CS;
             idt[vec_num].reserved4 = DISABLE;
             idt[vec_num].reserved3 = DISABLE;
             idt[vec_num].reserved2 = ENABLE;
             idt[vec_num].reserved1 = ENABLE;
             idt[vec_num].size = ENABLE;
             idt[vec_num].reserved0 = DISABLE;
             idt[vec_num].dpl = DISABLE;
             idt[vec_num].present = ENABLE;

             // set correct system call privilege level
             if(vec_num == SYS_CALL){
                 idt[vec_num].dpl = USER_MODE;
             }
         }
     }
 }

 /*
  * init_IDT
  *   DESCRIPTION: driver function that enables IDT
  *   INPUTS: none
  *   OUTPUTS: none
  *   RETURN VALUE: none
  *   SIDE EFFECTS: initialization of IDT
  */
 void init_IDT(void){
     // initialization of the table entry
 	 idt_entry_init();

     // fill the table
     idt_handler_init_asm();

     // fill the IDTR
     lidt(idt_desc_ptr);
 }

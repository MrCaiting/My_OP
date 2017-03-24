/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */
#include "i8259.h"
#include "lib.h"
#define ENABLE              1
#define MASK_IRQ2        0x04
#define MASTER_PIN_MAX      8
#define SLAVE_ON_MASTER     2

/* Interrupt masks to determine which interrupts
 * are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7 */
uint8_t slave_mask; /* IRQs 8-15 */

/*
 * i8259_init
 *   DESCRIPTION: Initialization of the mater and slave PIC chip, by sending
 *     four different Initialization Command Words
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Brings PIC into working stage
 */
void
i8259_init(void)
{
    /* Setup the mask that will be used during initialization */
    master_mask = 0xFF;
    slave_mask = 0xFF;

    /* Mask all the IR input and starts initialization */
    outb(master_mask,MASTER_8259_IMR);
    outb(slave_mask,MASTER_8259_IMR);

    /* Initializing the master chip */
    outb(ICW1,MASTER_8259_PORT);
    outb(ICW2_MASTER,MASTER_8259_IMR);
    outb(ICW3_MASTER,MASTER_8259_IMR);
    outb(ICW4,MASTER_8259_IMR);

    /* Initializing the slave chip */
    outb(ICW1,SLAVE_8259_PORT);
    outb(ICW2_SLAVE,SLAVE_8259_IMR);
    outb(ICW3_SLAVE,SLAVE_8259_IMR);
    outb(ICW4,SLAVE_8259_IMR);

    // mask the port again since we one to turn only a few of them
    // on in kernel.c to test interrupts
    outb(master_mask,MASTER_8259_IMR);
    outb(slave_mask,MASTER_8259_IMR);

}

/*
 * enable_irq
 *   DESCRIPTION: Enable a specified IRQ depend on the passed parameter
 *   INPUTS: irq_num -- The number of IRQ that are requested to be enabled
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Enable a specific irq
 */
void
enable_irq(uint32_t irq_num)
{
    /* If the pin number is located at the master PIC */
    if(irq_num < MASTER_PIN_MAX){
        master_mask = inb(MASTER_8259_IMR);
        // Enable the corresponding pin
        master_mask &= (uint8_t) (~(ENABLE << irq_num));
        outb(master_mask,MASTER_8259_IMR);
    }
    /* If the pin number is located at the slave PIC */
    else{
        master_mask = inb(MASTER_8259_IMR);
        master_mask &= (uint8_t) (~MASK_IRQ2);
        outb(master_mask,MASTER_8259_IMR);

        slave_mask = inb(SLAVE_8259_IMR);
        slave_mask &= (uint8_t) (~(ENABLE << (irq_num - MASTER_PIN_MAX)));
        outb(slave_mask,SLAVE_8259_IMR);
    }
}

/*
 * disable_irq
 *   DESCRIPTION: Similar to the function for enabling, this function disable a
 *      specified IRQ depend on the passed parameter
 *   INPUTS: irq_num -- The number of IRQ that are requested to be disabled
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Disable a specific irq
 */
void
disable_irq(uint32_t irq_num)
{
    /* If the pin number is located at the master PIC */
    if(irq_num < MASTER_PIN_MAX){
        master_mask = inb(MASTER_8259_IMR);
        master_mask |= (uint8_t) (ENABLE << irq_num);
        outb(master_mask,MASTER_8259_IMR);
    }
    /* If the pin number is located at the slave PIC */
    else{
        master_mask = inb(MASTER_8259_IMR);
        master_mask |=(uint8_t)(MASK_IRQ2);
        outb(master_mask,MASTER_8259_IMR);

        slave_mask = inb(SLAVE_8259_IMR);
        slave_mask |= (uint8_t) (ENABLE << (irq_num - MASTER_PIN_MAX));
        outb(slave_mask,SLAVE_8259_IMR);
    }
}

/*
 * send_eoi
 *   DESCRIPTION: Send end-of-interrupt signal for the specified IRQ
 *   INPUTS: irq_num -- The number of IRQ that are requested to be the target
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Signal the PIC with EOI signal
 */
void
send_eoi(uint32_t irq_num)
{
    uint8_t EOI_C;
    if(irq_num < MASTER_PIN_MAX){
        EOI_C = EOI | (uint8_t) irq_num;
        outb(EOI_C,MASTER_8259_PORT);
    }
    else{
        EOI_C = EOI | (uint8_t) (irq_num - MASTER_PIN_MAX);
        outb(EOI_C, SLAVE_8259_PORT);
        EOI_C = EOI | (uint8_t) (SLAVE_ON_MASTER);
        outb(EOI_C, MASTER_8259_PORT);
    }
}

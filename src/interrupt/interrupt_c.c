#include "interrupt.h"

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt)
{
    
}



void pic_acknowledge(unsigned int interrupt)
{
    if (interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT) {
        return;
    }
    if (interrupt < PIC2_START_INTERRUPT) {
        outb(PIC1_PORT_A, PIC_ACK);
    } else {
        outb(PIC2_PORT_A, PIC_ACK);
    }

}
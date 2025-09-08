#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../utility/data_types.h"

#define IDT_ENTRIES 256

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7

#define PIC_ACK 0x20


// Represents the full CPU state pushed by pusha instruction or manually
struct cpu_state {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esi;
    unsigned int edi;
    unsigned int ebp;
    unsigned int esp;   // Usually the esp before push if you saved it manually
    unsigned int ds;
    unsigned int es;
    unsigned int fs;
    unsigned int gs;
} __attribute__((packed));

// Represents the stack state pushed automatically by CPU on interrupt
struct stack_state {
    unsigned int error_code; // Only if the interrupt pushes an error code
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    //unsigned int user_esp;   // Only if switching from user mode
    //unsigned int ss;         // Only if switching from user mode
} __attribute__((packed));

struct idt_entry {
    uint16_t offset_low;   // lower 16 bits of handler function address
    uint16_t selector;     // code segment selector in GDT
    uint8_t  zero;         // always 0
    uint8_t  type_attr;    // type and attributes
    uint16_t offset_high;  // higher 16 bits of handler function address
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt);

void pic_acknowledge(unsigned int interrupt);

#endif
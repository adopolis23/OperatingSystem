#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "../utility/data_types.h"
#include "../io/io.h"
#include "../utility/utility.h"
#include "../io/keyboard.h"

#define IDT_ENTRIES 256

//todo: Move this to another file with defs
#define KEYBOARD_INTERRUPT 0x21

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7

#define PIC_ACK 0x20


static inline void cli(void) {
    __asm__ __volatile__("cli" ::: "memory");
}

static inline void sti(void) {
    __asm__ __volatile__("sti" ::: "memory");
}


// Represents the full CPU state pushed by pusha instruction or manually
struct cpu_state {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;   // Usually the esp before push if you saved it manually
    uint16_t ds;
    uint16_t es;
    //unsigned int fs;
    //unsigned int gs;
} __attribute__((packed));

// Represents the stack state pushed automatically by CPU on interrupt
struct stack_state {
    uint32_t eip;
    uint16_t cs;
    uint32_t eflags;
    uint32_t user_esp;   // Only if switching from user mode
    uint16_t ss;         // Only if switching from user mode
    //unsigned int error_code; // Only if the interrupt pushes an error code
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


// interrupts defined in interrupt.s
extern void interrupt_handler_33();
//


extern struct idt_entry idt[IDT_ENTRIES];
extern struct idt_ptr idt_ptr;

//not sure why we have to do this but we have to :)
void pic_remap();

void idt_init();

//perform remapping and init of the idt
void idt_init_all();

//defined in interrupt.s
void load_idt(uint32_t);

void interrupt_handler(struct cpu_state* cpu, struct stack_state* stack, unsigned int interrupt);

void idt_set_entry(uint8_t index, uint32_t base, uint16_t sel, uint8_t flags);

void pic_acknowledge(unsigned int interrupt);

#endif
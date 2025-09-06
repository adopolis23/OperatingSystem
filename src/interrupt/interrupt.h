#ifndef INTERRUPT_H
#define INTERRUPT_H

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


void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt);

#endif
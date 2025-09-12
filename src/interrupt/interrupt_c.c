#include "interrupt.h"

struct idt_entry idt[IDT_ENTRIES];
struct idt_ptr idt_ptr;

void interrupt_handler(struct cpu_state* cpu, struct stack_state* stack, unsigned int interrupt)
{
    #ifndef RELEASE_BUILD
        serial_write_string(SERIAL_COM1_BASE, "DEBUG: Common Interrupt Handler Triggered.\n");
    #endif

    if (interrupt == 0x21)
    {
        #ifndef RELEASE_BUILD
            serial_write_string(SERIAL_COM1_BASE, "DEBUG: Keyboard Interrupt Handler Triggered.\n");
        #endif
        keyboard_handler();
    }


}

void idt_set_entry(uint8_t index, uint32_t offset, uint16_t sel, uint8_t flags)
{
    idt[index].offset_low = offset & 0xFFFF;
    idt[index].offset_high = (offset >> 16) & 0xFFFF;

    idt[index].selector = sel;
    idt[index].zero = 0;
    idt[index].type_attr = flags;
}

void pic_remap()
{
    // Init PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20); // master offset 0x20
    outb(0xA1, 0x28); // slave offset 0x28
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    // Unmask IRQ1 (keyboard) on master PIC
    outb(0x21, 0xFD); // 11111101 = mask all except IRQ1
    outb(0xA1, 0xFF); // mask all slave IRQs
}

void idt_init()
{
    idt_ptr.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    idt_ptr.base = (uint32_t) &idt;

    // clear IDT
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_entry(i, 0, 0, 0);
    }

    idt_set_entry(0x21, (uint32_t)interrupt_handler_33, 0x08, 0x8E);

    load_idt((uint32_t) &idt_ptr);
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
        outb(PIC1_PORT_A, PIC_ACK);
    }
}

void idt_init_all()
{
    pic_remap();
    idt_init();
    asm volatile ("sti");  // enable interrupts

    char buf[11];
    itoa_hex(idt_ptr.base, buf);
    serial_log_msg("Base of IDT at: ", buf);
}
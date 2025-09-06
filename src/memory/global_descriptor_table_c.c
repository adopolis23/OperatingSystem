#include "global_descriptor_table.h"

void gdt_set_entry(struct gdt_entry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    entry->limit_low    = (limit & 0xFFFF); //lowest 2 bytes of limit
    entry->base_low     = (base & 0xFFFF); //lowest 2 bytes of base
    entry->base_middle  = (base >> 16) & 0xFF; //middle 2 bytes
    entry->access       = access; //access
    entry->granularity  = (limit >> 16) & 0x0F; // bits 16-19 of limit
    entry->granularity |= gran & 0xF0; //flags
    entry->base_high    = (base >> 24) & 0xFF; // heighest 2 bytes of base
}

struct gdt_entry gdt[3];
struct gdt_ptr gdt_p;

void gdt_init()
{
    //defines a flat gdt.

    gdt_p.limit = (sizeof(gdt) - 1);
    gdt_p.base = (uint32_t) &gdt;

    // Null descriptor
    gdt_set_entry(&gdt[0], 0, 0, 0, 0);

    // Code segment: base=0, limit=4GB, access=0x9A, gran=0xCF
    gdt_set_entry(&gdt[1], 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // Data segment: base=0, limit=4GB, access=0x92, gran=0xCF
    gdt_set_entry(&gdt[2], 0, 0xFFFFFFFF, 0x92, 0xCF);

    //defined in global_descriptor_table.s
    gdt_flush((uint32_t)&gdt_p);
}
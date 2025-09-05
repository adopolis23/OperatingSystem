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
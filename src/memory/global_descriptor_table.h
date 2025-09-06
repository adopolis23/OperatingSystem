#ifndef GLOBAL_DESCRIPTOR_H
#define GLOBAL_DESCRIPTOR_H

#include "../utility/data_types.h"


//defines an entry for the global descriptor table using a packed struct
//each entry should be 32 bytes long and describes where each segment starts and ends in memeory
struct gdt_entry
{
    uint16_t limit_low;     // bits 0–15 of segment limit
    uint16_t base_low;      // bits 0–15 of base
    uint8_t  base_middle;   // bits 16–23 of base
    uint8_t  access;        // access flags
    uint8_t  granularity;   // flags + bits 16–19 of limit
    uint8_t  base_high;     // bits 24–31 of base
} __attribute__((packed));

//defines the location of the gdt in memory withe a base and limit/size. 
struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

//sets the values of the gdt_entry correctly
void gdt_set_entry(struct gdt_entry* entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

void gdt_flush(uint32_t gdt_ptr);

//initiallize the gdt
void gdt_init();

//create actual global descriptor table and pointer to it
extern struct gdt_entry gdt[3];
extern struct gdt_ptr gdt_p;


#endif

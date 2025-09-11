#include "io/io.h"
#include "utility/utility.h"
#include "utility/data_types.h"
#include "memory/global_descriptor_table.h"
#include "interrupt/interrupt.h"
#include "multiboot/multiboot.h"


void kmain(unsigned int ebx)
{
    char buf[11];
    extern char _end;

    //log to serial port com1 - does not decrement sp
    serial_write_string(SERIAL_COM1_BASE, "Entry into kernel kmain successful\n");


    //print message in the frame buffer
    char* message = "Hello World!";  
    print_message_beginning_fb(message, 0, 2);
    clear_screen_after_position(12);

    //_end is defined in the linker script as the end of the kernel after the .bss section 
    itoa_hex((unsigned int) &_end, buf);
    serial_log_msg("Kernel end at: ", buf);

    //initialize the FLAT gdp
    gdt_init();

    //initialize the IDT
    idt_init_all();




    //find pointer to loaded program
    multiboot_info_t* mbinfo = (multiboot_info_t*) ebx;
    
    //checks if one module loaded and the modules info bit is valid in bit 3
    if (mbinfo->mods_count != 1 || !(mbinfo->flags & 0x8))
    {
        serial_write_string(SERIAL_COM1_BASE, "Error loading GRUB module\n");

        itoa_hex((unsigned int) mbinfo->mods_count, buf);
        serial_log_msg("Mods Count: ", buf);

        itoa_hex((unsigned int) mbinfo->flags, buf);
        serial_log_msg("Flags: ", buf);
    }
    unsigned int address_of_module = mbinfo->mods_addr;
    
    //itoa_hex(address_of_module, buf);
    //serial_log_msg("Address of Module: ", buf);

    ///starting program
    typedef void (*call_module_t)(void);
    call_module_t start_program = (call_module_t) address_of_module;
    start_program();
    //program must return to get to here;



    while(1)
    {
        //spin
    }
}
#include "io/io.h"
#include "io/screen.h"
#include "kshell/kshell.h"
#include "utility/utility.h"
#include "utility/data_types.h"
#include "memory/global_descriptor_table.h"
#include "interrupt/interrupt.h"
#include "multiboot/multiboot.h"
#include "io/keyboard.h"


void kmain(uint32_t magic, multiboot_info_t* mbinfo)
{
    char buf[11];
    extern char _end;

    //log to serial port com1 - does not decrement sp
    serial_write_string(SERIAL_COM1_BASE, "Entry into kernel kmain successful\n");

    //_end is defined in the linker script as the end of the kernel after the .bss section 
    itoa_hex((unsigned int) &_end, buf);
    serial_log_msg("Kernel end at: ", buf);

    //initialize the FLAT gdp
    gdt_init();

    //initialize the IDT
    idt_init_all();
    
    itoa_hex((unsigned int) mbinfo, buf);
    serial_log_msg("MBI at: ", buf);
    

    
    // load and jump into external program.
    // right now this program only loads 0xDEADBEEF into eax.
    if (mbinfo->mods_count > 0) {
        multiboot_module_t* mods = (multiboot_module_t*) mbinfo->mods_addr;
        
        uint32_t start = mods[0].mod_start;
        uint32_t end   = mods[0].mod_end;
        
        // for testing, dump the first byte
        unsigned char* prog = (unsigned char*) start;
        
        typedef void (*prog_entry_t)(void);
        prog_entry_t entry = (prog_entry_t) start;

        entry();   // jump into program   
    }
    //program must return to get to here;
    

    //init the kernel shell for text communication with kernel
    init_kshell();


    while(1)
    {
        //spin
    }
}
#include "io/io.h"
#include "utility/utility.h"
#include "utility/data_types.h"
#include "memory/global_descriptor_table.h"


void kmain(void)
{
    char buf[11];

    //log to serial port com1 - does not decrement sp
    serial_write_string(SERIAL_COM1_BASE, "Entry into kernel kmain successful\n");

    unsigned int sp = get_sp();
    itoa_hex(sp, buf);
    serial_write_string(SERIAL_COM1_BASE, "ESP = ");
    serial_write_string(SERIAL_COM1_BASE, buf);
    serial_write_string(SERIAL_COM1_BASE, "\n");


    //print message in the frame buffer
    char* message = "Hello World!";  
    print_message_beginning_fb(message, 0, 2);
    clear_screen_after_position(12);

    //_end is defined in the linker script as the end of the kernel after the .bss section 
    extern char _end;
    itoa_hex((unsigned int) &_end, buf);
    serial_log_msg("Kernel end at: ", buf);

    //initialize the FLAT gdp
    gdt_init();

    itoa_hex(gdt_p.base, buf);
    serial_log_msg("Base of GDT at: ", buf);


    


    while(1)
    {
        //spin
    }
}
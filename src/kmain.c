#include "io/io.h"
#include "utility/utility.h"
#include "utility/data_types.h"
#include "memory/global_descriptor_table.h"
#include "interrupt/interrupt.h"


void kmain(void)
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


    while(1)
    {
        //spin
    }
}
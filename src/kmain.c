#include "io/io.h"
#include "utility/utility.h"


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
    unsigned int kernel_end = (unsigned int) &_end;
    itoa_hex(kernel_end, buf);
    serial_write_string(SERIAL_COM1_BASE, "Kernel end at: ");
    serial_write_string(SERIAL_COM1_BASE, buf);
}
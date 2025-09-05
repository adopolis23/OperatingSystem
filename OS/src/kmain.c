#include "io/io.h"
#include "utility/utility.h"


void kmain(void)
{
    //log to serial port com1 - does not decrement sp
    serial_write_string(SERIAL_COM1_BASE, "Entry into kernel kmain successful\n");

    unsigned int sp = get_sp();
    char buf[11];
    itoa_hex(sp, buf);
    serial_write_string(SERIAL_COM1_BASE, "ESP = ");
    serial_write_string(SERIAL_COM1_BASE, buf);
    serial_write_string(SERIAL_COM1_BASE, "\n");


    //print message in the frame buffer
    char* message = "Hello World!";  
    print_message_beginning_fb(message, 0, 2);
    clear_screen_after_position(12);

}
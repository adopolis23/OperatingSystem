#include "io.h"




void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_EXPECT_HIGHEST_FIRST);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure(unsigned short com)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_transmit_fifo_empty(unsigned short com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com) & 0x20);
}

void serial_write_char(unsigned short com, char c)
{
    //blocking wait while fifo is not empty; may be better way to do this.
    while (serial_transmit_fifo_empty(com) == 0)
    {
        // do nothing; wait for fifo to be empty
    }

    //write the byte to the data port of com
    outb(SERIAL_DATA_PORT(com), c);

}

void serial_write_string(unsigned short com, const char* str)
{
    //while the current char still is valid, write the byte then advance the str pointer
    while(*str)
    {
        serial_write_char(com, *str++);
    }
}


//read the scan code from the keyboard data port
unsigned char read_scan_code(void)
{
    return inb(KBD_DATA_PORT);
}
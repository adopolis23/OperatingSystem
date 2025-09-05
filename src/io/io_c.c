#include "io.h"

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    // write text to framebuffer
    //fb now points to beginning address of frame buffer
    char* fb = (char*) 0x000B8000;

    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void print_message_beginning_fb(const char* message, unsigned char fg, unsigned char bg)
{
    unsigned int i = 0;
    while (message[i] != '\0')
    {
        fb_write_cell(i*2, message[i], fg, bg);
        i++;
    }

    fb_move_cursor(i);
}

void clear_screen_after_position(unsigned int pos)
{
    unsigned int i = pos;
    while (i < 2000)
    {
        fb_write_cell(i*2, ' ', 0, 0);
        i++;
    }
}




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

#include "screen.h"

void clear_screen_after_position(unsigned int pos)
{
    unsigned int i = pos;
    while (i < (SCREEN_ROWS * SCREEN_COLS))
    {
        fb_write_cell(i*2, ' ', 0, 0);
        i++;
    }
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



void clear_screen()
{
    unsigned int i = 0;
    while (i < (SCREEN_ROWS * SCREEN_COLS))
    {
        fb_write_cell(i*2, ' ', 0, 0);
        i++;
    }
}

void fb_move_cursor(unsigned short pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}


void screen_write_position(unsigned int row, unsigned int col, char c, unsigned char fg, unsigned char bg)
{
    unsigned int cell = (row*SCREEN_COLS + col) * 2;
    fb_write_cell(cell, c, fg, bg);
}


void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    // write text to framebuffer
    //fb now points to beginning address of frame buffer
    char* fb = (char*) 0x000B8000;

    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void move_cursor_position(unsigned int row, unsigned int col)
{
    unsigned int cell = (row*SCREEN_COLS + col) * 2;
    fb_move_cursor(cell);
}



#include "io/io.h"

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
}



void kmain(void)
{
    char* message = "Hello World!";  
    print_message_beginning_fb(message, 0, 2);
}
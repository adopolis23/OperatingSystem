#ifndef IO_H
#define IO_H

    //sends data to IO port, definition is in io.s
    //used to advance the cursor

    /* The I/O ports */
    #define FB_COMMAND_PORT 0x3D4
    #define FB_DATA_PORT 0x3D5

    /* The I/O port commands */
    #define FB_HIGH_BYTE_COMMAND 14
    #define FB_LOW_BYTE_COMMAND 15

    void outb(unsigned short port, unsigned char data);

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

#endif
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

    //defined in header becuase too lazy to put in body
    void fb_move_cursor(unsigned short pos)
    {
        outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
        outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
        outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
        outb(FB_DATA_PORT, pos & 0x00FF);
    }

#endif
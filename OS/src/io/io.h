#ifndef IO_H
#define IO_H

    //sends data to IO port, definition is in io.s
    //used to advance the cursor

    void outb(unsigned short port, unsigned char data);

#endif
#include "keyboard.h"


//handles the input from the kayboard by reading from port 0x60
void keyboard_handler()
{
    uint8_t scancode = inb(KBD_DATA_PORT);

    if (scancode & 0x80)
    {
        return;
    }

    char c = keymap[scancode];

    if (c)
    {
        // do something
    }

    pic_acknowledge(0x21);

}
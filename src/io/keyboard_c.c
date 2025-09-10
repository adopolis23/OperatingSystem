#include "keyboard.h"


unsigned char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
   '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,  '\\','z','x','c','v','b','n','m',',','.','/', 0, '*',
    0,   ' '
};

//handles the input from the kayboard by reading from port 0x60
void keyboard_handler()
{
    uint8_t scancode = inb(KBD_DATA_PORT);

    char buff[12];
    itoa_hex(scancode, buff);
    serial_log_msg("ScanCode: ", buff);

    if (!(scancode & 0x80)) {  // key press only
        
        pic_acknowledge(KEYBOARD_INT);

        char c = keymap[scancode];
        if (c) {
            char buf[2] = { c, '\0' };
            serial_log_msg("Key Pressed: ", buf);
        }
    }
    else
    {
        pic_acknowledge(KEYBOARD_INT);
    }


}
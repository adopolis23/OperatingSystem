#include "keyboard.h"


unsigned char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
   '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,  '\\','z','x','c','v','b','n','m',',','.','/', 0, '*',
    0,   ' '
};

unsigned char key_buffer[KEY_BUFFER_SIZE];
volatile unsigned int key_buffer_head = 0;
volatile unsigned int key_buffer_tail = 0;

//handles the input from the kayboard by reading from port 0x60
void keyboard_handler()
{
    char buff[12], c;
    uint8_t scancode = inb(KBD_DATA_PORT);

    itoa_hex(scancode, buff);
    serial_log_msg("ScanCode: ", buff);

    if (!(scancode & 0x80)) {  // key press only
        
        pic_acknowledge(KEYBOARD_INT);

        c = keymap[scancode];
        if (c) {
            char buf[2] = { c, '\0' };
            serial_log_msg("Key Pressed: ", buf);

            //handle inserting this character into circular buffer
            unsigned int next = (key_buffer_head + 1) % KEY_BUFFER_SIZE;
            if (next != key_buffer_tail)
            {
                key_buffer[key_buffer_head] = c;
                key_buffer_head = next;
            }
            else
            {
                serial_write_string(SERIAL_COM1_BASE, "KERNEL: Buffer Full.");
            }
        }
    }
    else
    {
        pic_acknowledge(KEYBOARD_INT);
    }

}

char get_key()
{

    if (key_buffer_tail != key_buffer_head)
    {
        //this case is buffer has key in it.
        //return key at tail position and advance tail
        char c = key_buffer[key_buffer_tail];
        key_buffer_tail = (key_buffer_tail + 1) % KEY_BUFFER_SIZE;
    }
    else
    {
        //this case is buffer empty
        //return 0
        return (char) 0;
    }

}
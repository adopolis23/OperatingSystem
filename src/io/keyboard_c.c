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
    uint8_t scancode = inb(KBD_DATA_PORT);  // read from keyboard port
    char c = keymap[scancode & 0x7F];       // mask out the release bit

    // Only handle key presses (high bit clear)
    if (!(scancode & 0x80) && c != 0) {
        unsigned int next = (key_buffer_head + 1) % KEY_BUFFER_SIZE;
        if (next != key_buffer_tail) {  // buffer not full
            key_buffer[key_buffer_head] = c;
            key_buffer_head = next;
        } else {
            // Buffer full, optionally ignore key or log
        }
    }

    // Acknowledge the PIC at the very end
    pic_acknowledge(KEYBOARD_INT);
}



char get_char()
{
    char c = 0;

    sti();

    if (key_buffer_tail != key_buffer_head) {
        c = key_buffer[key_buffer_tail];
        key_buffer_tail = (key_buffer_tail + 1) % KEY_BUFFER_SIZE;
    }

    cli();

    return c;  // sentinel for "no key"
}
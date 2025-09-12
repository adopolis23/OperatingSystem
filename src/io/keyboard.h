#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "../utility/data_types.h"
#include "../interrupt/interrupt.h"

#define KEYBOARD_INT 0x21

#define SHIFT_PRESSED1 0x2A
#define SHIFT_PRESSED2 0x36

#define SHIFT_RELEASED1 0xAA
#define SHIFT_RELEASED2 0xB6

#define KEY_MAP_SIZE 128
#define KEY_BUFFER_SIZE 16

// simple keymap for US layout, set 1 scan codes
extern unsigned char keymap[KEY_MAP_SIZE];

extern unsigned char key_buffer[KEY_BUFFER_SIZE];

//mark these as volatile to avoid compiler optimization
extern volatile unsigned int key_buffer_head;
extern volatile unsigned int key_buffer_tail;


void keyboard_handler();

char get_key();


#endif
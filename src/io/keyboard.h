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


// simple keymap for US layout, set 1 scan codes
extern unsigned char keymap[128];


void keyboard_handler();


#endif
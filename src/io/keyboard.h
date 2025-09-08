#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "../utility/data_types.h"
#include "../interrupt/interrupt.h"


#define SHIFT_PRESSED1 0x2A
#define SHIFT_PRESSED1 0x36

#define SHIFT_RELEASED1 0xAA
#define SHIFT_RELEASED1 0xB6


// simple keymap for US layout, set 1 scan codes
unsigned char keymap[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
   '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,   'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,  '\\','z','x','c','v','b','n','m',',','.','/', 0, '*',
    0,   ' '
};


void keyboard_handler();


#endif
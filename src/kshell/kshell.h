#ifndef KSHELL_H
#define KSHELL_H

#include "../io/screen.h"

// this will be a kernel shell that runs by default if none other are loaded.


#define SCREEN_ROWS 25
#define SCREEN_COLS 80

extern unsigned int row;
extern unsigned int col;


void init_kshell();


#endif
#ifndef KSHELL_H
#define KSHELL_H

#include "../io/screen.h"
#include "../io/keyboard.h"

// this will be a kernel shell that runs by default if none other are loaded.


#define SCREEN_ROWS 25
#define SCREEN_COLS 80

extern unsigned int cur_row;
extern unsigned int cur_col;


void init_kshell();

void advance_column();

void print_shell_intro();

void new_line();

void put_char(char c);

void write_cursor();

void run();


#endif
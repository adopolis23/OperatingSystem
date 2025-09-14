#ifndef SCREEN_H
#define SCREEN_H

#include "io.h"

#define SCREEN_ROWS 25
#define SCREEN_COLS 80

//color definitions
#define COLOR_BLACK 0
#define COLOR_BLUE 1
#define COLOR_GREEN 2
#define COLOR_CYAN 3
#define COLOR_RED 4
#define COLOR_MAGENTA 5
#define COLOR_BROWN 6
#define COLOR_WHITE 15

void clear_screen();

void clear_screen_after_position(unsigned int pos);

void fb_move_cursor(unsigned short pos);

void move_cursor_position(unsigned int row, unsigned int col);

void screen_write_position(unsigned int row, unsigned int col, char c, unsigned char fg, unsigned char bg);

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

void print_message_beginning_fb(const char* message, unsigned char fg, unsigned char bg);

#endif
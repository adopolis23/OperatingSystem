#include "kshell.h"


unsigned int cur_row = 0;
unsigned int cur_col = 0;



void init_kshell()
{
    clear_screen();

    run();
}

void advance_cursor_right()
{
    cur_col = (cur_col + 1) % SCREEN_COLS;
}

void write_cursor()
{

}


void run()
{
    while (1) {

        char input = get_char();
        if (input != '*') {
            //fb_write_cell(10, input, COLOR_WHITE, COLOR_BLACK);
            screen_write_position(cur_row, cur_col, input, COLOR_WHITE, COLOR_BLACK);

            advance_cursor_right();
        }

    }

}
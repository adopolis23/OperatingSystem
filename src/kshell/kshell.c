#include "kshell.h"


unsigned int cur_row = 0;
unsigned int cur_col = 0;



void init_kshell()
{
    clear_screen();

    print_shell_intro();

    run();
}

void advance_column()
{
    cur_col = (cur_col + 1) % SCREEN_COLS;
}

void print_shell_intro()
{
    put_char('$');
    put_char('>');
    put_char(' ');
}

void new_line()
{
    //set cursor to first position of next line
    cur_col = 0;
    cur_row = (cur_row + 1) % SCREEN_ROWS;

    print_shell_intro();
}

void put_char(char c)
{
    screen_write_position(cur_row, cur_col, c, COLOR_BLACK, COLOR_WHITE);
    move_cursor_position(cur_row, (cur_col+1)%SCREEN_COLS);

    advance_column();
}

void run()
{
    while (1) {

        char input = get_char();

        if (input != 0) {

            char buff[11];
            itoa_hex((unsigned int) input, buff);
            serial_log_msg("Char: ", buff);

            if (input == '\n')
            {
                new_line();
                continue;
            }

            put_char(input);
        }

    }

}

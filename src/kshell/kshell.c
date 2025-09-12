#include "kshell.h"


unsigned int cur_row = 0;
unsigned int cur_col = 0;



void init_kshell()
{
    clear_screen();
    //screen_write_position(1, 1, 'O', COLOR_WHITE, COLOR_BLACK);

    run();
}



void run()
{
    char input;

    while (1)
    {
        // wait until a key is available
        input = get_key();
        if (input == 0)
        {
            //asm volatile("hlt"); 
            continue;
        }

        // got input
        serial_log_msg("Got Key: ", (char[2]){ input, '\0' });

        screen_write_position(cur_row, cur_col, input, COLOR_WHITE, COLOR_BLACK);
        cur_col = (cur_col + 1) % SCREEN_COLS;
    }
}
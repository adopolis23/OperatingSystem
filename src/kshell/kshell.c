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
    char input = 0;

    while (1)
    {
        
        for (int i = 0; i < 1000000; i++)
        {
            int x = 0;
            int y = 1;
            int z = x + y * 2;
        }

        input = get_char();

        // if (input != 0)
        // {
        //     serial_log_msg("Char: ", (char[2]){ input, '\0' });
        //     screen_write_position(1, 1, input, COLOR_WHITE, COLOR_BLACK);
        //     //serial_write_string(SERIAL_COM1_BASE, "DEBUG\n");
        // }

    }
}
#include "kshell.h"


unsigned int row = 0;
unsigned int col = 0;



void init_kshell()
{
    clear_screen();
    screen_write_position(1, 1, 'O', COLOR_WHITE, COLOR_BLACK);
}
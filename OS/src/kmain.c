#include "io/io.h"


void kmain(void)
{
    char* message = "Hello World!";  
    print_message_beginning_fb(message, 0, 2);

    clear_screen_after_position(12);

}
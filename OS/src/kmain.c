
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
    // write text to framebuffer
    //fb now points to beginning address of frame buffer
    char* fb = (char*) 0x000B8000;

    fb[i] = c;
    fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void print_message_beginning_fb(char* message, unsigned char fg, unsigned char bg)
{
    int index = 0;
    int fb_index = 0;

    while (message[index] != '\0')
    {
        fb_write_cell(fb_index, message[index], fg, bg);
        index = index + 1;
        fb_index = fb_index + 2;
    }
    
}


void kmain(void)
{
    // char* message = "Hello";
    // print_message_beginning_fb(message, 2, 8);
    fb_write_cell(0, 'H', 2, 8);
    fb_write_cell(2, 'e', 2, 8);
    fb_write_cell(4, 'l', 2, 8);
    fb_write_cell(6, 'l', 2, 8);
    fb_write_cell(8, 'o', 2, 8);
}

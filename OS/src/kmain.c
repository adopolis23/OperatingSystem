
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

    while (message[index] != '\0')
    {
        fb_write_cell(index, message[index], fg, bg);
        index = index + 1;
    }
    
}


void kmain(void)
{
    print_message_beginning_fb("Hello World!", 2, 8);
}

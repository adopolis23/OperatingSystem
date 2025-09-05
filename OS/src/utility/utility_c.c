#include "utility.h"

void itoa_hex(unsigned int value, char* buffer)
{
    //buffer here would be length 11 theoretically
    const char* digits = "0123456789ABCDEF";

    //prefil first buffer spots with 0x
    buffer[0] = '0';
    buffer[1] = 'x';

    //loops through for each byte in the output, except the 9-1 reverses it
    for (int i = 0; i < 8; i++)
    {
        buffer[9-i] = digits[value & 0xF]; //value & 0xF here get only the least sig 4 bits of value
        value = value >> 4; // bitshift value over by 4 bits to get to the next 4 bits 
    }

    //null terminate
    buffer[10] = '\0';

}
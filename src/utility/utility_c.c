#include "utility.h"
#include "../io/io.h"

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

//this is not working right
void serial_write_sp()
{
    unsigned int sp = get_sp();
    char buf[11];
    itoa_hex(sp, buf);
    serial_write_string(SERIAL_COM1_BASE, "ESP = ");
    serial_write_string(SERIAL_COM1_BASE, buf);
    serial_write_string(SERIAL_COM1_BASE, "\n");
}

void serial_log_msg(const char* msg, const char* value)
{
    serial_write_string(SERIAL_COM1_BASE, msg);
    serial_write_string(SERIAL_COM1_BASE, value);
    serial_write_string(SERIAL_COM1_BASE, "\n");
}


void int_to_str(int value, char *str) {
    char buffer[12]; // enough for -2,147,483,648 + '\0'
    int i = 0, j = 0;
    int is_negative = 0;

    if (value == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    if (value < 0) {
        is_negative = 1;
        value = -value;
    }

    // extract digits in reverse order
    while (value > 0) {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    // reverse into output string
    while (i > 0) {
        str[j++] = buffer[--i];
    }
    str[j] = '\0';
}

void serial_debug_hex(uint32_t value)
{
    char buff[12];
    itoa_hex(value, buff);
    serial_log_msg("DEBUG HEX: ", buff);
}
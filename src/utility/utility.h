#ifndef UTILITY_H
#define UTILITY_H

#include "data_types.h"

    //returns the current stack pointer
    unsigned int get_sp();

    void serial_write_sp();

    //takes unsigned int value and places its hexidecimal ascii translation in buffer
    //preceded by a 0x
    void itoa_hex(unsigned int value, char* buffer);

    void serial_log_msg(const char* msg, const char* value);

    void int_to_str(int value, char *str);

    void serial_debug_hex(uint32_t value);

#endif
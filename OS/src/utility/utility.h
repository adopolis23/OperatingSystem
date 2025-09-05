#ifndef UTILITY_H
#define UTILITY_H

    //returns the current stack pointer
    unsigned int get_sp();

    //takes unsigned int value and places its hexidecimal ascii translation in buffer
    //preceded by a 0x
    void itoa_hex(unsigned int value, char* buffer);

#endif
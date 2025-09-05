#ifndef IO_H
#define IO_H

    //sends data to IO port, definition is in io.s
    //used to advance the cursor

    /* The I/O ports */
    #define FB_COMMAND_PORT 0x3D4
    #define FB_DATA_PORT 0x3D5

    /* The I/O port commands */
    #define FB_HIGH_BYTE_COMMAND 14
    #define FB_LOW_BYTE_COMMAND 15

    void outb(unsigned short port, unsigned char data);

    unsigned char inb(unsigned short port);

    void fb_move_cursor(unsigned short pos);

    void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);

    void print_message_beginning_fb(const char* message, unsigned char fg, unsigned char bg);

    void clear_screen_after_position(unsigned int pos);

    //configure the serial ports
    /* All the I/O ports are calculated relative to the data port. This is because
    * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
    * order, but they start at different values.
    */
    #define SERIAL_COM1_BASE 0x3F8 // COM1 base port 
    #define SERIAL_DATA_PORT(base) (base)
    #define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
    #define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
    #define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
    #define SERIAL_LINE_STATUS_PORT(base) (base + 5)

    /* SERIAL_LINE_EXPECT_HIGHEST_FIRST:
    * Tells the serial port to expect first the highest 8 bits on the data port,
    * then the lowest 8 bits will follow
    */
    #define SERIAL_LINE_EXPECT_HIGHEST_FIRST 0x80

    /** serial_configure_baud_rate:
    * Sets the speed of the data being sent. The default speed of a serial
    * port is 115200 bits/s. The argument is a divisor of that number, hence
    * the resulting speed becomes (115200 / divisor) bits/s.
    *
    * @param com The COM port to configure
    * @param divisor The divisor
    */

    void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

    /** serial_configure_line:
    * Configures the line of the given serial port. The port is set to have a
    * data length of 8 bits, no parity bits, one stop bit and break control
    * disabled.
    *
    * @param com The serial port to configure
    */
    void serial_configure(unsigned short com);

    //returns 1 if transmit queue is empty
    int serial_transmit_fifo_empty(unsigned short com);

    void serial_write_char(unsigned short com, char c);

    void serial_write_string(unsigned short com, const char* str);




#endif
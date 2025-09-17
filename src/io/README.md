# IO

These files deal with simple Input/Output operations, mainly serial operations which are the first input/output that are setup in the operating system.

### Inb / Outb

The two most basic functions here are `inb` and `outb`. inb reads data from a port, while outb send some specified data to a port.

### Writing Data to Serial

Data can now be writted to a port with the `void serial_write_char(unsigned short com, char c)` function. 

The default port specified is the `COM1` port. This ports base address is at `0x3F8` and other addresses for this port can be calculated from there.
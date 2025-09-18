ENTRY(loader) /* the name of the entry label */

SECTIONS {
    . = 0xC0100000; /* the code should be loaded at 1 MB */

    /* Multiboot header must be in the first 8 KiB */
    .multiboot ALIGN(0x1000) : AT(ADDR(.multiboot)-0xC0000000)
    {
        *(.multiboot)
    }

    .text ALIGN (0x1000) : AT(ADDR(.text)-0xC0000000) /* align at 4 KB */
    {
    *(.text) /* all text sections from all files */

    /* This trick here allows me to use char* string litterals by putting my ro data into my text area.*/
    *(.rodata*)
    }

    .data ALIGN (0x1000) : AT(ADDR(.data)-0xC0000000) /* align at 4 KB */
    {
    *(.data) /* all data sections from all files */
    }

    .bss ALIGN (0x1000) : AT(ADDR(.bss)-0xC0000000) /* align at 4 KB */
    {
    *(COMMON) /* all COMMON sections from all files */
    *(.bss) /* all bss sections from all files */
    _end = .;
    }
    
}

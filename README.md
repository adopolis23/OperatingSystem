# Custom Operating System

This project is a simple operating system that I built **from scratch** using **Assembly** and **C**, this work takes guidance and inspiration from:  

[*Operating Systems: Three Easy Pieces*](https://pages.cs.wisc.edu/~remzi/OSTEP/).

[*The Little Book About OS Development*](https://littleosbook.github.io/book.pdf).

The operating system uses **GRUB** as the bootloader, which is responsible for loading the kernel into memory during startup. From there, the kernel takes over execution and begins managing the system.  



## Kernel Loading and Memory Layout

At its core, the kernel is simply a program in **ELF format**. GRUB loads this program into memory at specific addresses defined by the `link.ld` linker script.  

- The kernel’s code is set to begin execution at **address `0x00100000`**, as specified in the linker script.  
- Addresses below `0x00100000` are reserved for low-level functionality, such as:  
  - **Memory-mapped I/O**  
  - **Frame buffer writing** (both of which this OS utilizes).  


The first of my own assembly code to get ran is in the `loader.s` file. The entry point is called loader and its purpose is to setup the stack and jump into the kernel C code entry point `kmain`.

## Build Instructions

### Tools Required
- `nasm`
- `ld`
- `gcc`
- `genisoimage`
- `qemu`

### Setup
Download the GRUB stage2 bootloader file:  

```bash
wget -O stage2_eltorito https://github.com/littleosbook/littleosbook/raw/master/files/stage2_eltorito
```

In order to build just the kernel.elf run:
```bash
make
```

In order to build the full .iso run:
```bash
make iso
```

To clean build files:
```bash
make clean
```

## Run Instructions

In order to run the iso in qemu run this command
```bash
qemu-system-i386 -cdrom os.iso
```

The following flag can be added to that command to allow debugging in the console, such as running `info registers` to view register contents.

```bash
-monitor stdio 
```

The following flag can be added to the command to view the output of the serial com port, this port is used for debugging information from the kernel.

```bash
-serial stdio 
```
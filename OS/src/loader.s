global loader

extern kmain ;external kernel entry point

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0 ; multiboot flags
CHECKSUM equ -(MAGIC_NUMBER + FLAGS) ; calculate the checksum
; (magic number + checksum + flags should equal 0)








section .text: ; start of the text (code) section
align 4 ; the code must be 4 (maybe 16?) byte aligned
    dd MAGIC_NUMBER ; write the magic number to the machine code,
    dd FLAGS ; the flags,
    dd CHECKSUM ; and the checksum


loader: ; the loader label (defined as entry point in linker script)
    ;mov eax, 0xCAFEBABE ; place the number 0xCAFEBABE in the register eax

    ; set up the stack pointer by setting esp to the base of the kernel stack plus the stack size 
    ; I think would give you address right after .bss section
    mov esp, kernel_stack + KERNEL_STACK_SIZE

    ; call into kernel main function
    call kmain

    ; loop forever do not exit
    .loop:
        jmp .loop




KERNEL_STACK_SIZE equ 8192 ; size of stack in bytes

section .bss
align 4 ; align at 4 bytes

kernel_stack: ; label points to beginning of memory
    resb KERNEL_STACK_SIZE ; reserve stack for the kernel



;example layout of memory at this point with the linker script as well
;0x00000000 ───────────────────────
;  IVT + BIOS data (real mode stuff)
;0x00007C00 ───────────────────────
;  Bootloader (stage 1)
;0x00080000 ───────────────────────
;  GRUB (itself in memory, relocatable)
;0x00100000 ───────────────────────
;  Your kernel starts here (from linker script)
;     [ .text   (code) ]
;     [ .rodata (consts, strings) ]
;     [ .data   (initialized globals) ]
;     [ .bss    (zeroed memory: stacks, arrays, etc.) ]
;     *  <- esp points here after next line.
;     ↑
;     kernel_stack (reserved 4 KB in .bss)
;0x00200000 ───────────────────────
;  Free RAM (you can use for heap, paging, allocators)
;...



[BITS 32]
[ORG 0x0]          ; offset 0 within the binary

_start:
    mov eax, 0xDEADBEEF

    ; infinite loop
    jmp $
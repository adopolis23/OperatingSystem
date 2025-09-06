
; defines function gdt_flush which tells the cpu where the descriptor table is.
; sets all segment registers to use this new table :)
global gdt_flush

gdt_flush:

    mov eax, [esp+4]
    lgdt [eax] ; load gdt with pointer from stack

    mov ax, 0x10 ; data segment selector (2nd entry, index 2) 
    mov ds, ax 
    mov es, ax 
    mov fs, ax 
    mov gs, ax 
    mov ss, ax 
    
    ; have to do a far jump to load the cs register aparently (0x08)
    jmp 0x08:.flush
    
    .flush: 
        ret


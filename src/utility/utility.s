global get_sp


; get_stack_pointer - returns the value of the current stack pointer esp
; ? due to us being in 32b protected mode this should be unsigned int ?
get_sp:
    mov eax, esp
    ret

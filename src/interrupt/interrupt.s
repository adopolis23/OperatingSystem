

extern interrupt_handler




common_inturrupt_handler:

    ; allocate space for cpu_state
    sub esp, 36
    mov [esp + 0], eax
    mov [esp + 4], ebx
    mov [esp + 8], ecx
    mov [esp + 12], edx
    mov [esp + 16], esi
    mov [esp + 20], edi
    mov [esp + 24], ebp
    mov [esp + 28], esp
    mov [esp + 32], ds
    mov [esp + 36], es

    ; prepare stack_state pointer
    ; stack_state is already pushed by CPU
    ; here esp + 36 means look past the cpu state we just pushed, +4 means look past the error code and then will be
    ; moving the start address of the stack state struct into eax
    mov eax, [esp + 36 + 4]   
    
    ; push arguments for C function (right-to-left)
    push dword [esp + 36]     ; interrupt number (already pushed in assembly handler)
    push eax                   ; pointer to stack_state
    push esp                   ; pointer to cpu_state

    call interrupt_handler

    ; clean up arguments
    add esp, 12

    ; restore cpu_state registers
    mov eax, [esp + 0]
    mov ebx, [esp + 4]
    mov ecx, [esp + 8]
    mov edx, [esp + 12]
    mov esi, [esp + 16]
    mov edi, [esp + 20]
    mov ebp, [esp + 24]
    mov esp, [esp + 28]
    mov ds, [esp + 32]
    mov es, [esp + 36]

    ; remove interrupt number & error code
    add esp, 8

    iret
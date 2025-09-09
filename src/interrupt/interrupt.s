

extern interrupt_handler

extern serial_debug_hex


common_interrupt_handler:

    mov edi, [esp]        ; int number
    mov esi, [esp+8]          ; ecx = handler_push_size

    ; push edx
    ; call serial_debug_hex
    ; add esp, 4

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

    mov ebx, [esp] ; pointer to cpu state

    ; prepare stack_state pointer
    ; stack_state is already pushed by CPU
    ; here esp + 36 means look past the cpu state we just pushed, +(4+ecx) means look past the error code and then will be
    ; moving the start address of the stack state struct into eax
    mov eax, [esp + 36 + 4 + esi]    ; pointer to stack state
    
    ;mov edx, edi
    push edi
    call serial_debug_hex
    add esp, 4

    ; push arguments for C function (right-to-left)
    push edi                    ; interrupt number (already pushed in assembly handler)
    push eax                   ; pointer to stack_state
    push ebx                   ; pointer to cpu_state

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

    ; remove interrupt number & error code & arg count
    add esp, 12

    iret





; Individual handlers

global interrupt_handler_0
interrupt_handler_0:
    push dword 8           ; tell the common int handler error code and int number pushed 
    push dword 0           ; fake error code
    push dword 0           ; interrupt number
    jmp common_interrupt_handler


global interrupt_handler_33
interrupt_handler_33:
    push dword 8 ; length of args
    push dword 0 ; error code
    push dword 33; int number
    jmp common_interrupt_handler


; load_idt - Loads the interrupt descriptor table (IDT).
; stack: [esp + 4] the address of the first entry in the IDT
; [esp ] the return address
global load_idt
load_idt:
    mov eax, [esp+4] ; load the address of the IDT into register eax
    lidt [eax] ; load the IDT
    ret ; return to the calling function
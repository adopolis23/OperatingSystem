.intel_syntax noprefix

.global _start
.extern main

_start:
    # Linux puts argc at [rsp], argv right after, then envp
    mov rdi, [rsp]
    lea rsi, [rsp+8]
    lea rdx, [rsi + rdi*8 + 8]

    call main

    # when main returns, exit with its return value
    mov rdi, rax
    mov rax, 60
    syscall

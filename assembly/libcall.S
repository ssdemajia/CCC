global main


extern printf

SECTION .text

main:
    push rbp
    mov rsi, message
    mov rdi, format
    call printf
    mov ax, 0
    pop rbp
    ret
format:
    db "output: %s", 0xa, 0
message:
    db "hello ss!", 0
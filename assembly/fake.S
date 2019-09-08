    .text
    .globl main

main:
    pushq %rbp
    movq %rsp, %rbp
    call _Z5printv
    movl $0, %eax
    popq %rbp
    ret

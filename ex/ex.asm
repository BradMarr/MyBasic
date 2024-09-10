section .text 
global _start 
_start: 
mov rax, 1 
mov rdi, 1 
mov rsi, lit_1 
mov rdx, 6 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, var_test 
mov rdx, len_var_test 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, lit_2 
mov rdx, 1 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, var_LF 
mov rdx, len_var_LF 
syscall 
mov rax, 60 
mov rdi, 0 
syscall 
section .data 
var_test db "Bob"
len_var_test equ $-var_test
section .bss 
section .rodata 
var_LF db 10
len_var_LF equ 1
lit_1 db "Hello ", 
lit_2 db "!", 

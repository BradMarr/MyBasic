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
mov rdx, 8 
syscall 
mov rax, 60 
mov rdi, 0 
syscall 
section .data 
var_test db "bob"
len_var_test equ $-var_test
lit_1 db "Hello ", 
lit_2 db "!", 10, 
section .bss 

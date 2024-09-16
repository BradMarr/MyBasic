section .text 
global _start 
_start: 
mov rax, [is_4] 
add [test_3], rax 
add byte [test_3], 48 
mov rax, 1 
mov rdi, 1 
mov rsi, lit_1 
mov rdx, 6 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, test_3 
mov rdx, len_test_3 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, lit_2 
mov rdx, 1 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, LF 
mov rdx, len_LF 
syscall 
mov rax, 60 
mov rdi, 0 
syscall 
section .data 
test_3 db 3
len_test_3 equ $-test_3
is_4 db 4
len_is_4 equ $-is_4
section .rodata 
LF db 10
len_LF equ 1
lit_1 db "Hello ", 
lit_2 db "!", 

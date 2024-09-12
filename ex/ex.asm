section .text 
global _start 
_start: 
mov rax, testa
add byte [testa], 2 
mov rax, testa
add byte [testa], 48 
mov rax, 1 
mov rdi, 1 
mov rsi, lit_1 
mov rdx, 6 
syscall 
mov rax, 1 
mov rdi, 1 
mov rsi, testa 
mov rdx, len_testa 
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
testa db 5
len_testa equ $-testa
section .bss 
section .rodata 
LF db 10
len_LF equ 1
lit_1 db "Hello ", 
lit_2 db "!", 

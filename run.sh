#!/bin/bash

echo "----COMPILING COMPILER----" 
g++ -std=c++23 compiler/main.cpp -o target/main

echo "-----RUNNING COMPILER-----" 
target/main "$@"

echo "-----ASSEMBLING CODE------" 
nasm -f elf64 ex/ex.asm

echo "-------LINKING CODE-------" 
ld ex/ex.o -o ex/ex
rm ex/ex.o

echo "-------RUNNING CODE-------" 
ex/ex "$@"
rm ex/ex
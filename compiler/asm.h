#pragma once

#include <fstream>
#include <vector>
#include "token.h"

void asm_exit(std::ofstream& output_file, std::string return_value, std::vector<std::string> data_section, std::vector<std::string> bss_section) {
    output_file <<
        "mov rax, 60 \n" <<
        "mov rdi, " + return_value + " \n" <<
        "syscall \n" <<
        "section .data \n";
    for (std::string data_item : data_section) {
        output_file << data_item << std::endl;
    }
    output_file << "section .bss \n";
    for (std::string bss_item : bss_section) {
        output_file << bss_item << std::endl;
    }
}

void asm_var(std::ofstream& output_file, std::string var_name, std::string var_size, Token var_value, std::vector<std::string>& data_section, int line_number, std::string pre ="var_") {
    std::string directive;
    if (var_size == "8") {
        directive = "db";
    } else if (var_size == "16") {
        directive = "dw";
    } else if (var_size == "32") {
        directive = "dd";
    } else if (var_size == "64") {
        directive = "dq";
    } else if (var_size == "80") {
        directive = "dt"; 
    } else {
        panic("Incorrect variable size (line " + std::to_string(line_number) + "): `" + var_size + "` is not a valid size. You can use either 8, 16, 32, 64, or 80 bits.");
    }

    std::string type_formatted_token;
    if (var_value.type == "string") {
        type_formatted_token = "\"" + var_value + "\"";
    } else {
        type_formatted_token = var_value;
    }

    data_section.push_back(pre + var_name + " " + directive + " " + type_formatted_token);
    data_section.push_back("len_var_" + var_name + " equ $-var_" + var_name);
}

void asm_print_var(std::ofstream& output_file, std::string var_name) {
    output_file << 
        "mov rax, 1 \n"
        "mov rdi, 1 \n"
        "mov rsi, var_" + var_name + " \n"
        "mov rdx, len_var_" + var_name + " \n"
        "syscall \n";
}
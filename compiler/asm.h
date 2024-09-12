#pragma once

#include <fstream>
#include <vector>
#include "token.h"

int string_literal_count = 0;

void asm_exit(std::ofstream& output_file, std::string return_value, std::vector<std::string> data_section, std::vector<std::string> bss_section, std::vector<std::string> rodata_section) {
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
    output_file << "section .rodata \n";
    for (std::string rodata_item : rodata_section) {
        output_file << rodata_item << std::endl;
    }
}

void asm_var(std::ofstream& output_file, std::string var_name, std::string var_size, Token& var_value, std::vector<std::string>& data_section, int line_number, std::string pre ="") {
    std::string directive;
    var_sizes.insert({var_name, var_size});
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
    data_section.push_back("len_" + var_name + " equ $-" + var_name);
}

void asm_print_var(std::ofstream& output_file, std::string var_name) {
    output_file << 
        "mov rax, 1 \n"
        "mov rdi, 1 \n"
        "mov rsi, " + var_name + " \n"
        "mov rdx, len_" + var_name + " \n"
        "syscall \n";
}

void asm_print_lit(std::ofstream& output_file, int lit_index, int lit_length) {
    output_file << 
        "mov rax, 1 \n"
        "mov rdi, 1 \n"
        "mov rsi, lit_" + std::to_string(lit_index) + " \n"
        "mov rdx, " + std::to_string(lit_length) + " \n"
        "syscall \n";
}

void asm_print(std::ofstream& output_file, std::vector<Token> print_items, std::vector<std::string>& rodata_section, int line_number) {
    int data_size = 0;
    string_literal_count += 1;
    std::string constructed_data = "lit_" + std::to_string(string_literal_count) + " db ";

    for (int i = 0; i < size(print_items); i++) {
        Token item = print_items[i];

        if (item.type == "string") {
            constructed_data += "\"" + item + "\", ";
            data_size += item.size();
        } else if (item.type == "char") {
            constructed_data += item + ", ";
            data_size += 1;
        } else if (item.type == "var") {
            if (constructed_data != "lit_" + std::to_string(string_literal_count) + " db ") {
                rodata_section.push_back(constructed_data);

                asm_print_lit(output_file, string_literal_count, data_size);
                string_literal_count += 1;
                data_size = 0;
                constructed_data = "lit_" + std::to_string(string_literal_count) + " db ";
            }

            asm_print_var(output_file, item);
        } else {
            panic("Incorrect data type (line " + std::to_string(line_number) + "): `" + item.type + "` can not be fed into print.");
        }
    }

    if (constructed_data != "lit_" + std::to_string(string_literal_count) + " db ") {
        rodata_section.push_back(constructed_data);

        asm_print_lit(output_file, string_literal_count, data_size);
        string_literal_count += 1;
        data_size = 0;
        constructed_data = "lit_" + std::to_string(string_literal_count) + " db ";
    }
}
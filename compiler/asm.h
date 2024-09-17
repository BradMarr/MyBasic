#pragma once

#include <fstream>
#include <vector>
#include "token.h"
#include "libs.h"

class ASM : public std::ofstream {
    public:
        int line_number = 1;

        ASM(const std::string& file_name, std::ios_base::openmode mode = std::ios::out)
            : std::ofstream(file_name, mode) {
                *this << 
                    "section .text \n"
                    "global _start \n"
                    "_start: \n";
            }

        void import(std::string item, std::string lib, std::vector<std::string>& rodata_section) {
            try {
                LIBS[lib][item](rodata_section);
            } catch (const std::bad_function_call& e) {
                panic("Invalid import (line " + std::to_string(line_number) + "): `" + item + "` in `" + lib + "` doesn't exist.");
            } catch (const std::exception& e) {
                panic(e.what());
            }
        }

        void add(std::string var, std::string value) {
            if (std::isdigit(value[0])) {
                *this <<
                    "add " + bits_to_operand_size(var_sizes[var]) + " [" + var + "], " + value + " \n";
            } else {
                *this <<
                    "mov rax, [" + value + "] \n"
                    "add [" + var + "], rax \n";
            }
        }

        void sub(std::string var, std::string value) {
            if (std::isdigit(value[0])) {
                *this <<
                    "sub " + bits_to_operand_size(var_sizes[var]) + " [" + var + "], " + value + " \n";
            } else {
                *this <<
                    "mov rax, [" + value + "] \n"
                    "sub [" + var + "], rax \n";
            }
        }

        void inc(std::string var) {
            *this <<
                "mov rax, " + var + "\n"
                "inc " + bits_to_operand_size(var_sizes[var]) + " [" + var + "] \n";
        }

        void dec(std::string var) {
            *this <<
                "mov rax, " + var + "\n"
                "dec " + bits_to_operand_size(var_sizes[var]) + " [" + var + "] \n";
        }

        void exit(std::string return_value, std::vector<std::string> data_section, std::vector<std::string> bss_section, std::vector<std::string> rodata_section) {
            *this <<
                "mov rax, 60 \n"
                "mov rdi, " + return_value + " \n"
                "syscall \n";

            if (!data_section.empty()) {
                *this << "section .data \n";
                for (std::string data_item : data_section) {
                *this << data_item << std::endl;
                }
            }
            if (!bss_section.empty()) {
                *this << "section .bss \n";
                for (std::string bss_item : bss_section) {
                    *this << bss_item << std::endl;
                }
            }
            if (!rodata_section.empty()) {
                *this << "section .rodata \n";
                for (std::string rodata_item : rodata_section) {
                    *this << rodata_item << std::endl;
                }
            }
        }

        void _(std::vector<Token> line) {
            for (Token item : line) {
                *this << item << " ";
            }
            *this << std::endl;
        }

        void var(std::string var_name, std::string var_size, Token& var_value, std::vector<std::string>& data_section, std::string pre ="") {
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

        void print_var(std::string var_name) {
            *this << 
                "mov rax, 1 \n"
                "mov rdi, 1 \n"
                "mov rsi, " + var_name + " \n"
                "mov rdx, len_" + var_name + " \n"
                "syscall \n";
        }

        void print_lit(int lit_index, int lit_length) {
            *this << 
                "mov rax, 1 \n"
                "mov rdi, 1 \n"
                "mov rsi, lit_" + std::to_string(lit_index) + " \n"
                "mov rdx, " + std::to_string(lit_length) + " \n"
                "syscall \n";
        }

        void print(std::vector<Token> print_items, std::vector<std::string>& rodata_section) {
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

                        print_lit(string_literal_count, data_size);
                        string_literal_count += 1;
                        data_size = 0;
                        constructed_data = "lit_" + std::to_string(string_literal_count) + " db ";
                    }

                    print_var(item);
                } else {
                    panic("Incorrect data type (line " + std::to_string(line_number) + "): `" + item.type + "` can not be fed into print.");
                }
            }

            if (constructed_data != "lit_" + std::to_string(string_literal_count) + " db ") {
                rodata_section.push_back(constructed_data);

                print_lit(string_literal_count, data_size);
                string_literal_count += 1;
                data_size = 0;
                constructed_data = "lit_" + std::to_string(string_literal_count) + " db ";
            }
        }
    private:
        int string_literal_count = 0;

        std::string bits_to_operand_size(std::string bits) {
            if (bits == "8") {
                return "byte";
            } else if (bits == "16") {
                return "word";
            } else if (bits == "32") {
                return "dword";
            } else if (bits == "64") {
                return "qword";
            } else if (bits == "80") {
                return "tword";
            } else if (bits == "128") {
                return "dqword";
            } else {
                panic("Invalid operand size (line " + std::to_string(line_number) + "): `" + bits + "` is an invalid size.");
                return "";
            }
        }
};
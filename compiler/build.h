#pragma once

#include <string>
#include <vector>
#include "frontend.h"
#include "asm.h"
#include "libs.h"

void build(std::string input_path, std::string output_path) {

    std::ifstream input_file(input_path);
    if (!input_file) {
        panic("Error opening file: " + input_path);
    }

    std::ofstream output_file(output_path, std::ofstream::trunc);
    output_file << 
        "section .text \n" <<
        "global _start \n" <<
        "_start: \n";

    std::string line;
    int line_number = 1;
    std::vector<std::string> data_section = {};
    std::vector<std::string> bss_section = {};
    std::vector<std::string> rodata_section = {};
    while(getline(input_file, line)) {
        if (size(line) == 0) {
            continue;
        }

        std::vector tokens = split(line, ' ');


        if (tokens[0] == "exit") {
            asm_exit(output_file, tokens[1], data_section, bss_section, rodata_section);
        } else if (tokens[0] == "_") {
            tokens.erase(tokens.begin());
            for (Token token : tokens) {
                output_file << token << " ";
            }
            output_file << std::endl;

        } else if (tokens[0] == "import") {
            try {
                LIBS[tokens[2]][tokens[1]](rodata_section);
            } catch (const std::bad_function_call& e) {
                panic("Invalid import (line " + std::to_string(line_number) + "): `" + tokens[1] + "` in `" + tokens[2] + "` doesn't exist.");
            } catch (const std::exception& e) {
                panic(e.what());
            }
        } else if (tokens[0] == "var") {
            asm_var(output_file, tokens[1], tokens[2], tokens[3], data_section, line_number);
        } else if (tokens[0] == "print") {
            if (tokens[1].type == "var") {
                asm_print_var(output_file, tokens[1]);
                continue;
            }

            tokens.erase(tokens.begin());
            asm_print(output_file, tokens, rodata_section, line_number);

        } else if (tokens[0] == "#") {
            ;
        } else {
            panic("Invalid syntax (line " + std::to_string(line_number) + "): `" + tokens[0] + "` is not a recognised command.");
        }
        line_number++;
    }

    input_file.close();
    output_file.close();
}
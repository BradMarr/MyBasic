#pragma once

#include <string>
#include <vector>
#include "frontend.h"
#include "asm.h"

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
    while(getline(input_file, line)) {
        std::vector tokens = split(line, ' ');


        if (tokens[0] == "exit") {
            asm_exit(output_file, tokens[1], data_section, bss_section);
        } else if (tokens[0] == "_") {
            tokens.erase(tokens.begin());
            for (Token token : tokens) {
                output_file << token << " ";
            }
            output_file << std::endl;


        } else if (tokens[0] == "var") {
            asm_var(output_file, tokens[1], tokens[2], tokens[3], data_section, line_number);
        } else if (tokens[0] == "print") {
            if (tokens[1].type == "var") {
                asm_print_var(output_file, tokens[1]);
                if (tokens.size() > 2) {
                    panic("Can only concatenate literals (line " + std::to_string(line_number) + "): Put var in separate print statement.");
                } 
                continue;
            }

            tokens.erase(tokens.begin());
            asm_print(output_file, tokens, data_section, line_number);

        } else {
            panic("Invalid syntax (line " + std::to_string(line_number) + "): `" + tokens[0] + "` is not a recognised command.");
        }
        line_number++;
    }

    input_file.close();
    output_file.close();
}
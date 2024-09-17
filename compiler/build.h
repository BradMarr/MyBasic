#pragma once

#include <string>
#include <vector>
#include "frontend.h"
#include "asm.h"
#include <cctype>

void build(std::string input_path, std::string output_path) {
    ASM ASM(output_path, std::ofstream::trunc);

    std::ifstream input_file(input_path);
    if (!input_file) {
        panic("Error opening file: " + input_path);
    }

    std::string line;
    std::vector<std::string> data_section = {};
    std::vector<std::string> bss_section = {};
    std::vector<std::string> rodata_section = {};
    while(getline(input_file, line)) {
        if (size(line) == 0) {
            continue;
        }

        std::vector tokens = split(line, ' ');

        if (tokens[0] == "exit") {
            ASM.exit(tokens[1], data_section, bss_section, rodata_section);
        } else if (tokens[0] == "_") {
            tokens.erase(tokens.begin());
            ASM._(tokens);

        } else if (tokens[0] == "import") {
            ASM.import(tokens[1], tokens[2], rodata_section);

        } else if (tokens[0] == "var") {
            ASM.var(tokens[1], tokens[2], tokens[3], data_section);

        } else if (tokens[0] == "print") {
            tokens.erase(tokens.begin());
            ASM.print(tokens, rodata_section);

        } else if (tokens[0] == "#") {
            ;
        } else if (tokens[0] == "add") {
            ASM.add(tokens[1], tokens[2]);
                
        } else if (tokens[0] == "sub") {
            ASM.sub(tokens[1], tokens[2]);
        } else if (tokens[0] == "inc") {
            ASM.inc(tokens[1]);
        } else if (tokens[0] == "dec") {
            ASM.dec(tokens[1]);
        } else {
            panic("Invalid syntax (line " + std::to_string(ASM.line_number) + "): `" + tokens[0] + "` is not a recognised command.");
        }
        ASM.line_number++;
    }

    input_file.close();
    ASM.close();
}
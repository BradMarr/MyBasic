#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <fstream>

using Lib = std::unordered_map<std::string, std::function<void(std::vector<std::string>&)>>;
using Libs = std::unordered_map<std::string, Lib>;

inline const void push_char(std::vector<std::string>& section, std::string var_name, int value) {
    section.push_back("var_" + var_name + " db " + std::to_string(value));
    section.push_back("len_var_" + var_name + " equ 1");
}

Libs LIBS = {
    {"chars", {
        {"LF", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "LF", 10);
        }},
        {"LF", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "LF", 10);
        }}
    }}
};
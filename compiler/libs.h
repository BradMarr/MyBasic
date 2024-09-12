#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include <fstream>

using Lib = std::unordered_map<std::string, std::function<void(std::vector<std::string>&)>>;
using Libs = std::unordered_map<std::string, Lib>;

inline const void push_char(std::vector<std::string>& section, std::string var_name, int value) {
    section.push_back(var_name + " db " + std::to_string(value));
    section.push_back("len_" + var_name + " equ 1");
}

Libs LIBS = {
    {"chars", {
        {"NUL", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "NUL", 0);
        }},
        {"SOH", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "SOH", 1);
        }},
        {"STX", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "STX", 2);
        }},
        {"ETX", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "ETX", 3);
        }},
        {"EOT", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "EOT", 4);
        }},
        {"ENQ", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "ENQ", 5);
        }},
        {"ACK", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "ACK", 6);
        }},
        {"BEL", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "BEL", 7);
        }},
        {"BS", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "BS", 8);
        }},
        {"TAB", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "TAB", 9);
        }},
        {"LF", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "LF", 10);
        }},
        {"VT", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "VT", 11);
        }},
        {"FF", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "FF", 12);
        }},
        {"CR", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "CR", 13);
        }},
        {"SO", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "SO", 14);
        }},
        {"SI", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "SI", 15);
        }},
        {"DLE", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "DLE", 16);
        }},
        {"DC1", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "DC1", 17);
        }},
        {"DC2", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "DC2", 18);
        }},
        {"DC3", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "DC3", 19);
        }},
        {"DC4", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "DC4", 20);
        }},
        {"NAK", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "NAK", 21);
        }},
        {"SYN", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "SYN", 22);
        }},
        {"ETB", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "ETB", 23);
        }},
        {"CAN", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "CAN", 24);
        }},
        {"EM", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "EM", 25);
        }},
        {"SUB", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "SUB", 26);
        }},
        {"ESC", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "ESC", 27);
        }},
        {"FS", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "FS", 28);
        }},
        {"GS", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "GS", 29);
        }},
        {"RS", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "RS", 30);
        }},
        {"US", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "US", 31);
        }},
        {"QUO", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "QUO", 34);
        }},
        {"DEL", [](std::vector<std::string>& rodata_section) { 
            push_char(rodata_section, "DEL", 127);
        }},
    }}
};
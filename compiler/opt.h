#pragma once

#include <string>
#include <iostream>

std::vector<std::string> file_to_lines

(const std::string& input_path) {
    std::fstream file(input_path, std::ios::in);
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}


void lines_to_file(const std::string& output_path, const std::vector<std::string>& lines) {
    std::fstream file(output_path, std::ios::out | std::ios::trunc);

    for (const auto& line : lines) {
        file << line << std::endl;
    }

    file.close();
}

void opt_passthrough(std::string input_path) {
    std::size_t pos = input_path.rfind('.');
    input_path = input_path.substr(0, pos) + ".asm";
    
    
}

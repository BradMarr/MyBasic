#include <cstddef>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "frontend.h"
#include "token.h"
#include "build.h"
#include "opt.h"

void help() {
    panic("You did something wrong.");
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        if (std::string(argv[1]) == "build") {
            if (argc == 3) {
                std::string input_path = argv[2];
                std::size_t pos = input_path.rfind('.');

                std::string output_path = input_path.substr(0, pos) + ".asm";

                build(argv[2], output_path);
            } else if (argc == 4) {
                build(argv[2], argv[3]);
            } else {
                help();
            }
        } else if (std::string(argv[1]) == "opt") {
            opt_passthrough(argv[2]);
        } else {
            std::cout << argv[1];
            help();
        }
    } else {
        help();
    }

    return 0;
}

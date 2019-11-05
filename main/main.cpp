#include <iostream>
#include <fstream>
#include <memory>

#include "parser/Lexer.hpp"
#include "parser/Parser.hpp"


int main(const int argc, const char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file.in" << std::endl;
        return 1;
    }
    std::ifstream stream(argv[1]);
    if (!stream) {
        std::cerr << "Can't open file: " << argv[1] << std::endl;
        return 1;
    }

    {
        auto testLexer = std::make_unique<Lexer>(stream);
        Parser parser(testLexer);
        parser.parse();
    }

    return 0;
}

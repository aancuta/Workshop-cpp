#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <vector>

#include "ast/Expression.h"
#include "ast/Identifier.h"
#include "ast/Number.h"

#include "parser/Lexer.h"
#include "parser/Parser.h"


int main(const int argc, const char** argv) {
    assert(argc == 2);
    std::ifstream stream(argv[1]);

    {
        auto testLexer = std::make_unique<Lexer>(stream);

        Parser parser(testLexer);
        parser.parse();
    }

    return 0;
}

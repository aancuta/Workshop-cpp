#ifndef _PARSER_H_
#define _PARSER_H_

#include <memory>

#include "Lexer.hpp"
#include "ast/ExpressionFactory.hpp"

class Identifier;

class Parser {
public:
    Parser(std::unique_ptr<Lexer>& lexer) : _lexer(std::move(lexer)) {}
    void parse();

private:
    template <typename T>
    void expectedToken(T t) const;
    void unexpectedToken() const;

    std::string match(Lexer::TOKEN_TYPE type) const;
    std::string match(const std::string& str) const;

    std::unique_ptr<Expression> parseBasic();
    std::unique_ptr<Identifier> parseIdentifier();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<Expression> parseBlock();
    std::unique_ptr<Expression> parseBinaryExpression(unsigned priority);
    std::unique_ptr<Expression> parseBinaryExpressionHelper(int priority, std::unique_ptr<Expression> expr);

    std::unique_ptr<Lexer> _lexer;
    ExpressionFactory _factory;
};

#endif

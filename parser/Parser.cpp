#include <memory>
#include <iostream>
#include <cassert>

#include "Parser.hpp"

#include "ast/BinaryExpression.hpp"
#include "ast/Expression.hpp"

using TOKEN_TYPE = Lexer::TOKEN_TYPE;

namespace {
    using OP_TYPE = BinaryExpression::OP_TYPE;
    const std::vector<std::unordered_set<BinaryExpression::OP_TYPE>> OP_PRECEDENCE {
        { OP_TYPE::ADD, OP_TYPE::SUBTRACT },
        { OP_TYPE::MULTIPLY, OP_TYPE::DIVIDE },
        { OP_TYPE::POW },
    };
}


template <typename T>
void Parser::expectedToken(T t) const {
    std::cerr << "Error at line: " << _lexer->getLine() << std::endl;
    std::cerr << "Expected " << t << " but got " << _lexer->getText() << std::endl;
    assert(false);
}

void Parser::unexpectedToken() const {
    std::cerr << "Error at line: " << _lexer->getLine() << std::endl;
    std::cerr << "Unexpected " << _lexer->getText() << std::endl;
    assert(false);
}

std::string Parser::match(TOKEN_TYPE type) const {
    if (_lexer->getToken() != type) {
        expectedToken((int)type);
    }
    auto text = _lexer->getText();
    _lexer->consume();
    return text;
}

std::string Parser::match(const std::string& str) const {
    if (_lexer->getText() != str) {
        expectedToken(str);
    }
    _lexer->consume();
    return str;
}

std::unique_ptr<Expression> Parser::parseBlock() {
    match("{");
    auto block = _factory.makeBlock();
    if (_lexer->getText() != "}") {
        for (;;) {
            block->addExpression(parseExpression());
            if (_lexer->getText() != "}") {
                match(";");
            } else {
                break;
            }
        }
    }
    match("}");
    return block;
}

std::unique_ptr<Expression> Parser::parseExpression() {
    return parseBinaryExpression(0); 
}

std::unique_ptr<Expression> Parser::parseBinaryExpression(unsigned priority) {
    if (priority >= OP_PRECEDENCE.size()) {
        return parseBasic();
    }

    std::unique_ptr<Expression> result = parseBinaryExpression(priority + 1);
    const auto& crtOps = OP_PRECEDENCE[priority];
    const auto it = BinaryExpression::CHAR_TO_OP.find(_lexer->getText());
    if (it != BinaryExpression::CHAR_TO_OP.end() &&
        crtOps.find(it->second) != crtOps.end()) {
            match(it->first); // "eat" the operator
            result = _factory.makeBinary(std::move(result), parseBinaryExpression(priority), it->second);
    }

    return result;
}

std::unique_ptr<Expression> Parser::parseBasic() {
    std::unique_ptr<Expression> result = nullptr;

    switch(_lexer->getToken()) {
    case TOKEN_TYPE::NUMBER: {
        result = _factory.makeNumber(match(TOKEN_TYPE::NUMBER));
        break;
    }
    case TOKEN_TYPE::IDENTIFIER: {
        auto identifier = parseIdentifier();
        if (_lexer->getText() == "=") {
            match("=");
            result = _factory.makeAssignment(std::move(identifier), parseExpression());
        } else {
            result = std::move(identifier);
        }
        break;
    }
    case TOKEN_TYPE::UNDEFINED: {
        match("undefined");
        result = _factory.makeUndefined();
        break;
    }
    case TOKEN_TYPE::PRINT: {
        match("print");
        result = _factory.makePrint(parseExpression());
        break;
    }
    case TOKEN_TYPE::OPERATOR: {
        if (_lexer->getText() == "(") {
            match("(");
            result = parseExpression();
            match(")");
        } else if (_lexer->getText() == "{") {
            return parseBlock();
        } else if (_lexer->getText() == "-") {
            match("-");
            return _factory.makeUnary(parseBasic(), UnaryExpression::OP_TYPE::SUBTRACT);
        } else if (_lexer->getText() == "+") {
            match("+");
            return _factory.makeUnary(parseBasic(), UnaryExpression::OP_TYPE::ADD);
        } else {
            unexpectedToken();
        }
        break;
    }
    case TOKEN_TYPE::IF: {
        match("if");
        match("(");
        auto condition = parseExpression();
        match(")");
        auto thenExpr = parseExpression();
        decltype(thenExpr) elseExpr = _factory.makeUndefined();
        if (_lexer->getToken() == TOKEN_TYPE::ELSE) {
            match("else");
            elseExpr = parseExpression();
        }
        return _factory.makeConditional(std::move(condition), std::move(thenExpr), std::move(elseExpr));
    }
    default:
        break;
    }

    return result;
}

std::unique_ptr<Identifier> Parser::parseIdentifier() {
    return _factory.makeIdentifier(match(TOKEN_TYPE::IDENTIFIER));
}

void Parser::parse() {
    _lexer->consume();
    if (_lexer->getToken() != TOKEN_TYPE::END) {
        auto expr = parseExpression();
        if (_lexer->getToken() != TOKEN_TYPE::END) {
            expectedToken((int)TOKEN_TYPE::END);
        }
        DumpGraph::dumpGraph(*expr);
        expr->getAsValue();
    }
}

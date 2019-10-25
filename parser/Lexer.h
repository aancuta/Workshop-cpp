#ifndef _LEXER_H_
#define _LEXER_H_

#include <fstream>
#include <string>
#include <unordered_set>
#include <ctype.h>

class Lexer {
public:
    Lexer(std::istream& stream) : _stream(stream) {}

    enum class TOKEN_TYPE {
        OPERATOR,
        IDENTIFIER,
        NUMBER,
        IF,
        ELSE,
        UNDEFINED,
        PRINT,
        END,
    };

    std::string getText() const {
        return _currentText;
    }

    TOKEN_TYPE getToken() const {
        return _currentToken;
    }

    TOKEN_TYPE consume();

private:
    std::istream& _stream;

    std::string _currentText = "";
    TOKEN_TYPE _currentToken = TOKEN_TYPE::END;

    const std::unordered_set<std::string> OPERATORS = { "*", "+", "-", "/", "(", ")", ";", "=", "{", "}", "**" };

    bool textEnded() const {
        return _stream.eof();
    }

    // TODO: refactor for less duplicate code?
    bool isDigit() const {
        return !textEnded() && std::isdigit(_stream.peek());
    }
    bool isOperator() const {
        if (textEnded()) {
            return false;
        }
        auto extension = _currentText + static_cast<char>(_stream.peek());
        return OPERATORS.find(extension) != OPERATORS.end();
    }
    bool isAlpha() const {
        return !textEnded() && std::isalpha(_stream.peek());
    }
    bool isWhiteSpace() const {
        return !textEnded() && std::isspace(_stream.peek());
    }
};

#endif

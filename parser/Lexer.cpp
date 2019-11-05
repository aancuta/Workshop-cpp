#include <iostream>
#include <cassert>

#include "Lexer.hpp"

namespace {
    enum class STATE {
        INT,
        OPERATOR,
        DIGIT,
        ALPHA,
    };
    std::ostream& operator << (std::ostream& stream, const STATE& state) {
        switch(state) {
            case STATE::INT:
                stream << "INT";
                break;
            case STATE::OPERATOR:
                stream << "OPERATOR";
                break;
            case STATE::DIGIT:
                stream << "DIGIT";
                break;
            case STATE::ALPHA:
                stream << "ALPHA";
                break;
        }
        return stream;
    }
}

int Lexer::readChar() {
    const int result = _stream.get();
    const unsigned char uc = static_cast<unsigned char>(result);
    if (uc == '\n' || uc == '\r') {
        _line++;
    }
    return result;
}

Lexer::TOKEN_TYPE Lexer::consume() {
    while (isWhiteSpace()) {
        readChar();
    }
    _currentText.clear();

    STATE state = STATE::INT;

    for (;;) {
        // std::cout << state << ' ' << static_cast<char>(_stream.peek()) << std::endl;
        switch (state) {
            case STATE::INT: {
                if (textEnded()) {
                    return _currentToken = TOKEN_TYPE::END;
                } else if (isOperator()) {
                    state = STATE::OPERATOR;
                } else if (isDigit()) {
                    state = STATE::DIGIT;
                } else if (isAlpha()) {
                    state = STATE::ALPHA;
                } else {
                    assert(false);
                }
                break;
            }
            case STATE::OPERATOR: {
                if (!isOperator()) {
                    return _currentToken = TOKEN_TYPE::OPERATOR;
                }

                _currentText += readChar();
                break;
            }
            case STATE::DIGIT: {
                if (!isDigit()) {
                    return _currentToken = TOKEN_TYPE::NUMBER;
                }

                _currentText += readChar();
                break;
            }
            case STATE::ALPHA: {
                if (!isAlpha()) {
                    if (_currentText == "if") {
                        return _currentToken = TOKEN_TYPE::IF;
                    } else if (_currentText == "else") {
                        return _currentToken = TOKEN_TYPE::ELSE;
                    } else if (_currentText == "undefined") {
                        return _currentToken = TOKEN_TYPE::UNDEFINED;
                    } else if (_currentText == "print") {
                        return _currentToken = TOKEN_TYPE::PRINT;
                    }

                    return _currentToken = TOKEN_TYPE::IDENTIFIER;
                }

                _currentText += readChar();
                break;
            }
        }
    }
}

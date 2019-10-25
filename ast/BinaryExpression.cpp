#include "BinaryExpression.h"
#include "Undefined.h"
using OP_TYPE = BinaryExpression::OP_TYPE;


const std::unordered_map<std::string, OP_TYPE> BinaryExpression::CHAR_TO_OP {
    { "+", OP_TYPE::ADD },
    { "-", OP_TYPE::SUBTRACT },
    { "*", OP_TYPE::MULTIPLY },
    { "/", OP_TYPE::DIVIDE },
    { "**", OP_TYPE::POW },
};

std::shared_ptr<Value> BinaryExpression::getAsValue() {
    // TODO
    return nullptr;
}

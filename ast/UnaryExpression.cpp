
#include "UnaryExpression.h"

#include "Number.h"
#include "Undefined.h"

#include <memory>

using OP_TYPE = UnaryExpression::OP_TYPE;


const std::unordered_map<std::string, OP_TYPE> UnaryExpression::CHAR_TO_OP {
    { "+", OP_TYPE::ADD },
    { "-", OP_TYPE::SUBTRACT },
};

std::shared_ptr<Value> UnaryExpression::getAsValue() {
    // TODO
    return nullptr;
}


#include "Constant.hpp"
#include "Expression.hpp"

std::shared_ptr<Constant> Expression::getAsConstant() {
    return getAsValue()->getAsConstant();
}

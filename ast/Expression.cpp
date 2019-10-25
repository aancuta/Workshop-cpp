
#include "Constant.h"
#include "Expression.h"

std::shared_ptr<Constant> Expression::getAsConstant() {
    return getAsValue()->getAsConstant();
}

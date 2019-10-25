#ifndef _VALUE_H_
#define _VALUE_H_

#include "Expression.h"

/**
 * A Value is an entity that can be saved in the symbol table.
 * It can either be a Block or a Constant.
 * In other words, we can save a Constant in the symbol table
 * or we can save code that will be evaluated at a future time.
 */
class Value : public Expression {
};

#endif

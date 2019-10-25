#ifndef _PRINT_EXPRESSION_H_
#define _PRINT_EXPRESSION_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "Expression.h"
#include "Number.h"

/**
 * A PrintExpression is an Expression that contains a child operand.
 * The operand will be converted to a Constant and than it will be
 * printed to the standard output.
 * The printed Constant is the result of the print operation.
 * Example:
 * "print print 8" will first print "8" and than print the result
 * of this expression, which is also "8". This results in the value
 * "8" being printed two times.
 */
class PrintExpression final : public Expression {
public:

    PrintExpression(std::unique_ptr<Expression>&& expr) : _expr(std::move(expr)) {}

    std::shared_ptr<Value> getAsValue() final {
        // TODO
        return nullptr;
    }

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const PrintExpression&);
private:
    std::unique_ptr<Expression> _expr;
};

#endif

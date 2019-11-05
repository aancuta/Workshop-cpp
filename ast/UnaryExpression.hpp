#ifndef _UNARY_EXPRESSION_H_
#define _UNARY_EXPRESSION_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Expression.hpp"
#include "Number.hpp"

/**
 * A UnaryExpression is an Expression that contains an operand and an
 * operator that will be performed on this operand.
 * A basic example is "-2", a UnaryExpression that contains a Number as
 * the operand and "-" as the operation.
 * A UnaryExpression will convert its operand to a Constant before
 * performing the actual operation.
 */
class UnaryExpression final : public Expression {
public:
    enum class OP_TYPE : int {
        ADD,
        SUBTRACT,
    };
    static const std::unordered_map<std::string, OP_TYPE> CHAR_TO_OP;

    UnaryExpression(std::unique_ptr<Expression>&& expr, OP_TYPE opType) : _expr(std::move(expr)), _opType(opType) {
        assert(_expr);
    }

    std::shared_ptr<Value> getAsValue() final;

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const UnaryExpression&);
private:
    std::unique_ptr<Expression> _expr;
    OP_TYPE _opType;
};

#endif

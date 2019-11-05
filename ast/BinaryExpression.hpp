#ifndef _BINARY_EXPRESSION_H_
#define _BINARY_EXPRESSION_H_

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "Expression.hpp"
#include "Number.hpp"

/**
 * A BinaryExpression is an Expression that contains a LHS (left hand side)
 * operand, a RHS (right hand side) operand and an operator that will be
 * performed on these 2 operands.
 * A basic example is "2 + a", a BinaryExpression that contains a Number as
 * LHS, an Identifier as RHS and adds the 2 values.
 * A BinaryExpressions will convert its operands to Constants before
 * performing the actual operation.
 */
class BinaryExpression final : public Expression {
public:
    enum class OP_TYPE : int {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        POW,
    };
    static const std::unordered_map<std::string, OP_TYPE> CHAR_TO_OP;

    BinaryExpression(std::unique_ptr<Expression>&& left, std::unique_ptr<Expression>&& right, OP_TYPE opType) : _left(std::move(left)), _right(std::move(right)), _opType(opType) {
        assert(_left);
        assert(_right);
    }

    std::shared_ptr<Value> getAsValue() final;

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const BinaryExpression&);
private:
    std::unique_ptr<Expression> _left;
    std::unique_ptr<Expression> _right;
    OP_TYPE _opType;
};

#endif

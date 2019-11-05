
#ifndef _CONDITIONAL_EXPRESSION_H_
#define _CONDITIONAL_EXPRESSION_H_

#include "Expression.hpp"
#include "Number.hpp"

/**
 * A ConditionalExpression is an if-statement. It has a condition Expression,
 * a then Expression and an else Expression
 * The result of an if statement is controlled by the evaluation of the condition.
 * If the condition is a non-zero Number this evaluates to the then Expression.
 * Otherwise we evaluate to the else Expression.
 * Note that in the language itself the else Expression is optional, but the
 * AST always has one.
 * If the else is missing in the input file, the parser will insert an Undefined
 * as the else Expression.
 * A ConditionalExpression will convert its condition to a Constant in order to
 * evaluate its result, but the then/else Expressions will be returned as Value.
 */
class ConditionalExpression : public Expression {
public:
    ConditionalExpression(std::unique_ptr<Expression>&& condition, std::unique_ptr<Expression>&& thenExpr, std::unique_ptr<Expression>&& elseExpr)
        : _condition(std::move(condition)), _thenExpr(std::move(thenExpr)), _elseExpr(std::move(elseExpr)) {
        assert(_condition);
        assert(_thenExpr);
        assert(_elseExpr);
    }

    std::shared_ptr<Value> getAsValue() final {
        // TODO
        return nullptr;
    }

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const ConditionalExpression&);
private:
    std::unique_ptr<Expression> _condition;
    std::unique_ptr<Expression> _thenExpr;
    std::unique_ptr<Expression> _elseExpr;
};

#endif

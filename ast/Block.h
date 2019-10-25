#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <ostream>

#include "Constant.h"

/**
 * A Block is a list of 0 or more Expression elements.
 * The list is evaluated in order and the Value of the Block
 * is the Value of the last Expression.
 * If the Block is empty, the resulting value is Undefined.
 */
class Block final : public Value {
public:
    void addExpression(std::shared_ptr<Expression> expression) {
        _expressions.push_back(std::move(expression));
    }
    
    std::shared_ptr<Value> getAsValue() final;

    std::shared_ptr<Constant> getAsConstant() final;

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const Block&);
private:
    std::vector<std::shared_ptr<Expression>> _expressions;
};

#endif

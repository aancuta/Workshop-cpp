#ifndef _ASSIGNMENT_H_
#define _ASSIGNMENT_H_

#include <iostream>
#include <memory>
#include <string>

#include "Expression.h"
#include "Identifier.h"

/**
 * An Assignment is an Expression that contains an Identifier and a
 * child Expression.
 * This evaluates to the same Value as the child Expression, after
 * it updates the Value held by the Identifier to that Expression.
 * The following Expression will evaluate to 5:
 * a = 1 + a = 4
 * The "a" Identifier is set to 4 and the resulting Expression is added with 1.
 * The resulting sum is than saved to "a" and the Assignment will evaluate to
 * this sum (i.e. 5).
 */
class Assignment final : public Expression {
public:
    Assignment(std::unique_ptr<Identifier>&& left, std::unique_ptr<Expression>&& right) : _id(std::move(left)), _expr(std::move(right)) {}

    std::shared_ptr<Value> getAsValue() final {
        // TODO
        return nullptr;
    }

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const Assignment&);

    std::unique_ptr<Identifier> _id;
    std::unique_ptr<Expression> _expr;
};

#endif

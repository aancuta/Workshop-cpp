#ifndef _UNDEFINED_H_
#define _UNDEFINED_H_

#include "Number.h"

#include <iostream>

/**
 * An Undefined Value is a special Value, different than 0,
 * but will evaluate as 0 when we invoke the getAsNumber method.
 * This Value can be produced by reading the Value of an identifier
 * that has not been set or by evaluating an empty Block.
 * 
 * Undefined is an "absorbant" element:
 * x op Undefined == Undefined op x == Undefined
 */
class Undefined : public Constant {

    void dumpValue(std::ostream& out) const final {
        out << "undefined";
    }

    void dump() const final {
        DumpGraph::dump(*this);
    }

    /**
     * Converts Undefined to the Number 0.
     * @returns the Number 0
     */
    std::shared_ptr<Number>getAsNumber() const final {
        // TODO
        return nullptr;
    }

    std::shared_ptr<Constant> getAsConstant() {
        // TODO
        return nullptr;
    }

    bool isUndefined() const final {
        return true;
    }

    friend void DumpGraph::dump(const Undefined&);
};

#endif

#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include "Value.hpp"

class Number;

/**
 * A Constant can either be a Number or the Undefined value.
 */
class Constant : public Value {
public:
    virtual bool isUndefined() const {
        return false;
    }

    /**
     * Convert this Constant to a Number.
     * For numbers, this will return a new instance with the same numerical
     * value.
     * For Undefined, it returns the Number 0.
     * @returns the Number
     */
    virtual std::shared_ptr<Number> getAsNumber() const = 0;

    std::shared_ptr<Constant> getAsConstant() = 0;

    std::shared_ptr<Value> getAsValue() final {
        // TODO
        return nullptr;
    }

    virtual void dumpValue(std::ostream& out) const = 0;
};

std::ostream& operator << (std::ostream& out, Constant& c);

#endif

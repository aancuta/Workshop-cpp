#ifndef _NUMBER_H_
#define _NUMBER_H_

#include <iostream>

#include "Constant.hpp"

/**
 * A Number is a Value that can be used in an Expression.
 * The given language only supports Number and Undefined as values.
 */
class Number final : public Constant {
public:
    Number(const int number = 0) : _number(number) {}
    Number(const std::string& str) : Number(std::atoi(str.c_str())) {}

    void dumpValue(std::ostream& out) const final {
        out << _number;
    }

    void dump() const final {
        DumpGraph::dump(*this);
    }

    /**
     * Create a new instance of Number, with the same numerical value as
     * the current Number.
     * @returns the Number
     */
    std::shared_ptr<Number> getAsNumber() const final {
        // TODO
        return nullptr;
    }

    std::shared_ptr<Constant> getAsConstant() {
        // TODO
        return nullptr;
    }

    operator int() const { return _number; }

    friend void DumpGraph::dump(const Number&);

private:
    const int _number;
};

#endif

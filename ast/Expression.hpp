#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <cassert>
#include <memory>

#include "DumpGraph.hpp"

class Value;
class Constant;

/**
 * Expression is an abstract class.
 * In this AST, everything is an expression (including blocks and
 * if-statements). In other words, every AST node extends Expression.
 */
class Expression {
public:

    /**
     * Evaluate all the children of this Expression and combine the
     * result in a single Value.
     * This method is a pure virtual method and it's implementation
     * semantics depends on the actual Expression.
     * @returns the Value of this Expression.
     */
    virtual std::shared_ptr<Value> getAsValue() = 0;

    /**
     * Evaluate this Expression as a Constant (Number or Undefined)
     * The default implementation for this method is to obtain the
     * Value of this Expression and call getAsConstant on that Value.
     * @returns the Constant result of this Expression.
     */
    virtual std::shared_ptr<Constant> getAsConstant();

    /**
     * Dump the expression in a format that can be graphically visualized at
     * http://www.webgraphviz.com/
     */
    virtual void dump() const = 0;

    /**
     * Virtual destructor is needed for std::unique_ptr
     */
    virtual ~Expression() = default;
};

#endif

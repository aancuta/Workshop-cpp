#ifndef _DUMP_GRAPH_H_
#define _DUMP_GRAPH_H_

class Assignment;
class BinaryExpression;
class Block;
class ConditionalExpression;
class Expression;
class Identifier;
class Number;
class PrintExpression;
class UnaryExpression;
class Undefined;

namespace DumpGraph {

    void dumpGraph(const Expression&);

    void dump(const Assignment&);
    void dump(const BinaryExpression&);
    void dump(const Block&);
    void dump(const ConditionalExpression&);
    void dump(const Identifier&);
    void dump(const Number&);
    void dump(const PrintExpression&);
    void dump(const UnaryExpression&);
    void dump(const Undefined&);

}

#endif
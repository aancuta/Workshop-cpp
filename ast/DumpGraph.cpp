
#include "DumpGraph.h"

#include "Assignment.h"
#include "BinaryExpression.h"
#include "Block.h"
#include "ConditionalExpression.h"
#include "Expression.h"
#include "Identifier.h"
#include "Number.h"
#include "PrintExpression.h"
#include "UnaryExpression.h"
#include "Undefined.h"

#include <iostream>
#include <memory>
#include <algorithm>

namespace {
    template <typename T>
    std::string getOpChar(typename T::OP_TYPE opType) {
        auto& CHAR_TO_OP = T::CHAR_TO_OP;
        auto it = std::find_if(CHAR_TO_OP.begin(), CHAR_TO_OP.end(), [opType] (const std::pair<std::string, typename T::OP_TYPE>& p) {
            return opType == p.second;
        });

        return it != CHAR_TO_OP.end() ? it->first : "?";
    }

    template <typename T>
    void dumpLabel(const Expression& e, const T& label) {
        std::cout << "Node" << &e << "[label=\"" << label << "\"]" << std::endl;
    }

    void dumpChildren(const Expression& s) {}

    template<typename T, typename... Args>
    void dumpChildren(const Expression& s, T& value, Args&... args) {
        std::cout << "Node" << &s << " -> " << "Node" << value << std::endl;
        value->dump();
        dumpChildren(s, args...);
    }
}

void DumpGraph::dumpGraph(const Expression& param) {
    std::cout << "digraph prof {" << std::endl;
    param.dump();
    std::cout << "}" << std::endl;
}

void DumpGraph::dump(const Assignment& param) {
    dumpLabel(param, "=");
    dumpChildren(param, param._id, param._expr);
}

void DumpGraph::dump(const BinaryExpression& param) {
    dumpLabel(param, getOpChar<BinaryExpression>(param._opType));
    dumpChildren(param, param._left, param._right);
}

void DumpGraph::dump(const Block& param) {
    dumpLabel(param, "{}");
    for (const auto& e : param._expressions) {
        dumpChildren(param, e);
    }
}

void DumpGraph::dump(const ConditionalExpression& param) {
    dumpLabel(param, "if");
    dumpChildren(param, param._condition, param._thenExpr, param._elseExpr);
}

void DumpGraph::dump(const Identifier& param) {
    dumpLabel(param, param.getName());
}

void DumpGraph::dump(const Number& param) {
    dumpLabel(param, param.get());
}

void DumpGraph::dump(const PrintExpression& param) {
    dumpLabel(param, "print");
    dumpChildren(param, param._expr);
}

void DumpGraph::dump(const UnaryExpression& param) {
    dumpLabel(param, getOpChar<UnaryExpression>(param._opType));
    dumpChildren(param, param._expr);
}

void DumpGraph::dump(const Undefined& param) {
    dumpLabel(param, "undefined");
}

std::ostream& operator << (std::ostream& out, Constant& c) {
    c.dumpValue(out);
    return out;
}

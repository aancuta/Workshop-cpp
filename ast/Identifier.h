#ifndef _IDENTIFIER_H_
#define _IDENTIFIER_H_

#include <string>

#include "Expression.h"
#include "Number.h"
#include "SymbolMap.h"

/**
 * An Identifier is a named Value that can be obtained using the getAsValue
 * method and that can be updated using the setValue method.
 * The Identifier holds the name of the variable while the Value itself
 * is stored in the symbol map.
 */
class Identifier final : public Expression {
public:
    Identifier(std::string Identifier, SymbolMap& symbolMap) : _id(Identifier), _symbolMap(symbolMap) {}

    std::shared_ptr<Value> getAsValue() final {
        // TODO
        return nullptr;
    }

    void setValue(std::shared_ptr<Value> value) {
        _symbolMap.addSymbol(_id, value);
    }

    std::string getName() const {
        return _id;
    }

    void dump() const final {
        DumpGraph::dump(*this);
    }

    friend void DumpGraph::dump(const Identifier&);
private:
    const std::string _id;
    SymbolMap& _symbolMap;
};

#endif

#ifndef _SYMBOL_MAP_H_
#define _SYMBOL_MAP_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "Number.h"
#include "Undefined.h"

class SymbolMap {
public:
    SymbolMap() = default;

    void addSymbol(const std::string& symbol, std::shared_ptr<Value> value) {
        _map.erase(symbol);
        _map.insert({symbol, value});
    }

    std::shared_ptr<Value> getValue(const std::string& symbol) {
        auto it = _map.find(symbol);
        if (it == _map.end()) {
            return std::make_unique<Undefined>();
        }
        return it->second;
    }
private:
    std::unordered_map<std::string, std::shared_ptr<Value> > _map;
};

#endif

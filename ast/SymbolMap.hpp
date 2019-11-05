#ifndef _SYMBOL_MAP_H_
#define _SYMBOL_MAP_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "Number.hpp"
#include "Undefined.hpp"

class SymbolMap {
public:
    SymbolMap() = default;

    void addSymbol(const std::string& symbol, const std::shared_ptr<Value>& value) {
        _map.erase(symbol);
        _map.insert({symbol, value});
    }

    const std::shared_ptr<Value> getValue(const std::string& symbol) {
        const auto it = _map.find(symbol);
        if (it == _map.end()) {
            return std::make_unique<Undefined>();
        }
        return it->second;
    }
private:
    std::unordered_map<std::string, const std::shared_ptr<Value> > _map;
};

#endif

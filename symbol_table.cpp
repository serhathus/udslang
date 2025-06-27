#include "symbol_table.h"

bool SymbolTable::add_variable(const std::string &name) {
    if (table.find(name) != table.end())
        return false;
    table[name] = 0;
    return true;
}

bool SymbolTable::set_variable(const std::string &name, int value) {
    auto it = table.find(name);
    if (it == table.end())
        return false;
    it->second = value;
    return true;
}

bool SymbolTable::get_variable(const std::string &name, int &value) const {
    auto it = table.find(name);
    if (it == table.end())
        return false;
    value = it->second;
    return true;
}


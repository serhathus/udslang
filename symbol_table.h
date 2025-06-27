#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <unordered_map>

class SymbolTable {
public:
    bool add_variable(const std::string &name);
    bool set_variable(const std::string &name, int value);
    bool get_variable(const std::string &name, int &value) const;
private:
    std::unordered_map<std::string, int> table;
};

#endif // SYMBOL_TABLE_H


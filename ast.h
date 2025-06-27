#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include "symbol_table.h"

class Expression {
public:
    virtual ~Expression() {}
    virtual int eval(SymbolTable& sym) const = 0;
};

class NumberExpr : public Expression {
public:
    int value;
    NumberExpr(int v):value(v){}
    int eval(SymbolTable&) const override { return value; }
};

class VariableExpr : public Expression {
public:
    std::string name;
    VariableExpr(const std::string &n):name(n){}
    int eval(SymbolTable& sym) const override {
        int v;
        if(!sym.get_variable(name,v)) {
            fprintf(stderr, "Undefined variable %s\n", name.c_str());
            return 0;
        }
        return v;
    }
};

class BinaryExpr : public Expression {
public:
    int op; //1==,2>,3<
    Expression *left,*right;
    BinaryExpr(int o, Expression* l, Expression* r):op(o),left(l),right(r){}
    ~BinaryExpr(){ delete left; delete right; }
    int eval(SymbolTable& sym) const override {
        int lv=left->eval(sym), rv=right->eval(sym);
        switch(op){
            case 1: return lv==rv;
            case 2: return lv>rv;
            case 3: return lv<rv;
        }
        return 0;
    }
};

class Statement {
public:
    virtual ~Statement(){}
    virtual void exec(SymbolTable& sym) const = 0;
};

class IntDeclStmt : public Statement {
public:
    std::string name;
    IntDeclStmt(const std::string &n):name(n){}
    void exec(SymbolTable& sym) const override {
        if(!sym.add_variable(name))
            fprintf(stderr, "Variable %s already declared\n", name.c_str());
    }
};

class AssignStmt : public Statement {
public:
    std::string name;
    Expression* expr;
    AssignStmt(const std::string &n, Expression* e):name(n),expr(e){}
    ~AssignStmt(){ delete expr; }
    void exec(SymbolTable& sym) const override {
        int v = expr->eval(sym);
        if(!sym.set_variable(name,v))
            fprintf(stderr, "Undefined variable %s\n", name.c_str());
    }
};

class PrintStmt : public Statement {
public:
    std::string text;
    PrintStmt(const std::string &t):text(t){}
    void exec(SymbolTable&) const override { printf("%s\n", text.c_str()); }
};

class SendUdsStmt : public Statement {
public:
    std::string text;
    SendUdsStmt(const std::string &t):text(t){}
    void exec(SymbolTable&) const override { printf("senduds: %s\n", text.c_str()); }
};

class ReadDidStmt : public Statement {
public:
    std::string text;
    ReadDidStmt(const std::string &t):text(t){}
    void exec(SymbolTable&) const override { printf("readdid: %s\n", text.c_str()); }
};

class BlockStmt : public Statement {
public:
    std::vector<Statement*> stmts;
    ~BlockStmt(){ for(auto s:stmts) delete s; }
    void exec(SymbolTable& sym) const override {
        for(auto s:stmts) s->exec(sym);
    }
};

class IfStmt : public Statement {
public:
    Expression* cond;
    BlockStmt* block;
    IfStmt(Expression* c, BlockStmt* b):cond(c),block(b){}
    ~IfStmt(){ delete cond; delete block; }
    void exec(SymbolTable& sym) const override {
        if(cond->eval(sym)) block->exec(sym);
    }
};

class WhileStmt : public Statement {
public:
    Expression* cond;
    BlockStmt* block;
    WhileStmt(Expression* c, BlockStmt* b):cond(c),block(b){}
    ~WhileStmt(){ delete cond; delete block; }
    void exec(SymbolTable& sym) const override {
        while(cond->eval(sym)) block->exec(sym);
    }
};

class Program {
public:
    std::vector<Statement*> stmts;
    ~Program(){ for(auto s:stmts) delete s; }
    void exec(SymbolTable& sym) const {
        for(auto s:stmts) s->exec(sym);
    }
};

#endif // AST_H

%{
#include <cstdio>
#include <cstdlib>
#include "ast.h"

static Program* root;
static SymbolTable symtab;

void yyerror(const char* s);
int yylex(void);
%}

%code requires {
class Expression;
class Statement;
class BlockStmt;
class Program;
}

%union {
    int ival;
    char* sval;
    Expression* expr;
    Statement* stmt;
    BlockStmt* block;
    Program* prog;
}

%token <sval> ID STRING
%token <ival> NUMBER
%token INT PRINT SENDUDS READDID IF WHILE EQ GT LT

%type <expr> expression
%type <stmt> statement
%type <block> block
%type <prog> program

%%
program
    : /* empty */ { $$ = new Program(); root = $$; }
    | program statement { $1->stmts.push_back($2); $$ = $1; }
    ;

statement
    : INT ID ';' { $$ = new IntDeclStmt($2); free($2); }
    | ID '=' expression ';' { $$ = new AssignStmt($1,$3); free($1); }
    | PRINT '(' STRING ')' ';' { $$ = new PrintStmt($3); free($3); }
    | SENDUDS '(' STRING ')' ';' { $$ = new SendUdsStmt($3); free($3); }
    | READDID '(' STRING ')' ';' { $$ = new ReadDidStmt($3); free($3); }
    | IF '(' expression ')' block { $$ = new IfStmt($3,$5); }
    | WHILE '(' expression ')' block { $$ = new WhileStmt($3,$5); }
    ;

block
    : '{' program '}' { $$ = new BlockStmt(); $$->stmts.swap($2->stmts); delete $2; }
    ;

expression
    : NUMBER { $$ = new NumberExpr($1); }
    | ID { $$ = new VariableExpr($1); free($1); }
    | expression EQ expression { $$ = new BinaryExpr(1,$1,$3); }
    | expression GT expression { $$ = new BinaryExpr(2,$1,$3); }
    | expression LT expression { $$ = new BinaryExpr(3,$1,$3); }
    ;

%%
void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
}

Program* get_root() { return root; }
SymbolTable& get_symtab() { return symtab; }


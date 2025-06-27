#include <cstdio>
#include <cstdlib>

extern int yyparse();
extern FILE* yyin;

class Program; // forward
class SymbolTable; // forward

Program* get_root();
SymbolTable& get_symtab();

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }
    yyin = fopen(argv[1], "r");
    if(!yyin) {
        perror("fopen");
        return 1;
    }
    if(yyparse() == 0) {
        Program* root = get_root();
        SymbolTable& sym = get_symtab();
        if(root)
            root->exec(sym);
    }
    fclose(yyin);
    return 0;
}


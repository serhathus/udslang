%option noyywrap
%{
#include "parser.tab.h"
#include <cstdio>
#include <cstring>
%}

%%
[ \t\r\n]+          ;
"int"               { return INT; }
"print"             { return PRINT; }
"senduds"           { return SENDUDS; }
"readdid"           { return READDID; }
"if"                { return IF; }
"while"             { return WHILE; }
"=="                { return EQ; }
">"                 { return GT; }
"<"                 { return LT; }
"{"                 { return '{'; }
"}"                 { return '}'; }
"("                 { return '('; }
")"                 { return ')'; }
";"                 { return ';'; }
"="                 { return '='; }
\"([^\\\"]|\\.)*\"     { yylval.sval=strdup(yytext+1); yylval.sval[strlen(yylval.sval)-1]='\0'; return STRING; }
[0-9]+              { yylval.ival=atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval=strdup(yytext); return ID; }
.                    { return yytext[0]; }
%%

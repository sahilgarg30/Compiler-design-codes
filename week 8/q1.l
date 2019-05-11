%{
#include "q1.tab.h"
%}
%%
"=" {printf("%s", yytext); return EQ;}
"+"|"-" {printf("%s", yytext); return ADDOP;}
"*"|"/"|"%" {printf("%s", yytext); return MULOP;}
"=="|"!="|"<="|">="|">"|"<" {printf("%s", yytext); return RELOP;}
"&&"|"||" {printf("%s", yytext); return LOP;}
[0-9]+ {printf("%s", yytext); return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {printf("%s", yytext); return ID;}
"(" {printf("%s", yytext); return LB;}
")" {printf("%s", yytext); return RB;}
%%

int yywrap()
{
	return 1;
}

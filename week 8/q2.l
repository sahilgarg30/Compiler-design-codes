%{
#include "q2.tab.h"
int cnt = 0;
%}
%%
"for" {printf("%s", yytext); return FOR;}
"main" {printf("%s", yytext); return MAIN;}
"while" {printf("%s", yytext); return WHILE;}
"if" {cnt++; printf("%s", yytext); return IF;}
"else" {printf("%s", yytext); return ELSE;}
"int" {printf("%s", yytext);return INT;}
"char" {printf("%s", yytext);return CHAR;}
"=" {printf("%s", yytext); return EQ;}
"+"|"-" {printf("%s", yytext); return ADDOP;}
"*"|"/"|"%" {printf("%s", yytext); return MULOP;}
"=="|"!="|"<="|">="|">"|"<" {printf("%s", yytext); return RELOP;}
[0-9]+ {printf("%s", yytext); return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {printf("%s", yytext); return ID;}
";" {printf("%s", yytext); return SC;}
"(" {printf("%s", yytext); return LB;}
")" {printf("%s", yytext); return RB;}
"[" {printf("%s", yytext); return LSB;}
"]" {printf("%s", yytext); return RSB;}
"{" {printf("%s", yytext); return LCB;}
"}" {printf("%s", yytext); return RCB;}
%%

int yywrap()
{
	printf("\nDepth: %d\n", cnt);
	return 1;
}

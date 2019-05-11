%{
#include "q3.tab.h"
#include <stdlib.h>
%}
%%
[ \t]+ {}
[0-9]+ {yylval=atof(yytext); return NUMBER;}
"*" return TIMES;
"/" return DIVIDE;
"+" return PLUS;
"-" return MINUS;
%%
int yywrap(){return 1;}


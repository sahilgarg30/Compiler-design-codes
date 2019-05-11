%{
#include "q2.tab.h"
%}
%%
" " {}
\n {return NL ;}
"if" {return IF;}
"else" {return ELSE;}
"<"|">"|"<="|">="|"=="|"!=" {return RELOP;}
"+"|"-" {return ADDOP;}
"/"|"*"|"%" {return MULOP;}
[0-9]+ {return NUM; }
[a-zA-Z][a-zA-Z0-9_]* {return ID; }
. {return yytext[0];}
%%

int yywrap(){
	return 1;
}
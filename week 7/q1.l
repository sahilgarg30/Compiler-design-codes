%{
#include "q1.tab.h"
%}
%%
" " {}
\n {return NL ;}
"int"|"char" {return DATA; }
[a-zA-Z][a-zA-Z0-9_]* {return ID; }
. {return yytext[0];}
%%

int yywrap(){
	return 1;
}
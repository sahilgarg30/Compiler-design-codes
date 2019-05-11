%{
#include "q4.tab.h"
%}
%%
" " {}
\n {return NL ;}
[0-9]+ {return NUM; }
. {return yytext[0];}
%%

int yywrap(){
	return 1;
}
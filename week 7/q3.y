%{
#include <stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}

%token PLUS MINUS NUMBER TIMES DIVIDE 
%left PLUS MINUS TIMES DIVIDE 
%%
S : expr { $$=$1; printf("%d\n",$$);}
	;
expr: term { $$=$1; }
	| expr MINUS term { $$=$1-$3; }
	| expr PLUS term { $$=$1+$3; }
	;
term: term TIMES factor { $$=$1*$3; }
| term DIVIDE factor { $$=$1/$3; }
| factor {$$=$1;}
;
factor: NUMBER {$$ =$1;}

%%

int yyerror(char *s) {
  printf("%s\n", s);
}

int main() {
	yyin = fopen("in2.txt","r");
	do{
		if(yyparse()){
			printf("Error\n");
			exit(1);
		}
	}while(!feof(yyin));
	printf("Successful"); 
}

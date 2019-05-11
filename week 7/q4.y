%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}

%token NL NUM
%left '+' '-' '/' '*' '^'

%%
inp : input NL {printf("Valid"); exit(0);}
	;
input : input exp
	|
	;
exp : NUM
	| exp exp '+'
	| exp exp '-'
	| exp exp '*'
	| exp exp '/'
	| exp exp '^'
	| exp 'n'
%%

int yyerror(char *msg)
{
printf("Invalid Expression \n");
exit(0);
}
void main ()
{
	yyin = fopen("in.txt","r");
	do{
		if(yyparse()){
			printf("Error\n");
			exit(1);
		}
	}while(!feof(yyin));
	printf("Successful");
}
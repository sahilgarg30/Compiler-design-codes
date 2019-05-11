%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}


%token EQ ADDOP MULOP RELOP LOP ID NUMBER LB RB

%%
expn: simple_expn eprime lprime
	;
simple_expn: term seprime
	;
term: factor tprime
	;
factor: ID
	| NUMBER
	;
tprime: MULOP factor tprime
	|
	;
seprime: ADDOP term seprime
	|
	;
eprime: RELOP simple_expn
	|
	;
lprime: LOP simple_expn eprime lprime
	|
	;
%%

int yyerror(char *msg)
{
printf("Invalid Expression\n");
return 1;
}
void main ()
{
yyin=fopen("in2.txt","r");
do
{
	if(yyparse())
	{
	printf("failure");
	exit(0);
	}
}while(!feof(yyin));
printf("\nSuccess\n");
}
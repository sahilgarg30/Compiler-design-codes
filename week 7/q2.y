%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
int count = 0;
extern FILE *yyin;
%}

%token ELSE IF NL NUM ID ADDOP RELOP MULOP
%left ';'
%left ','

%%
dec : decision NL { printf("Valid Expression\n"); printf("Nesting level - %d",count); exit(0);}
	;

decision :IF '(' exp ')' '{' stmtlist '}' dprime
		;

stmtlist : decision stmtlist {count++;} 
		| ';'
		|
		;
dprime : ELSE '{' stmtlist '}'
		|
		;  

exp : simplex eprime
		;

simplex : term seprime
		;

eprime : RELOP simplex
		|
		;

term : factor tprime
		;

seprime : ADDOP term seprime
		|
		;

tprime : MULOP factor tprime
		|
		;

factor : ID
		|NUM
		;

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
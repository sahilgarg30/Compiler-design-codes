%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}

%token ID NL DATA
%left ';'
%left ','

%%
stmt : exp NL { printf("Valid Expression"); exit(0);}
		;

exp : DATA idlist ';' exp
		|  
		;
idlist : ID
		|ID ',' idlist
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
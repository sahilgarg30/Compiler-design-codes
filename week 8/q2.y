%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
extern FILE *yyin;
%}


%token MAIN INT CHAR FOR WHILE IF ELSE EQ ADDOP MULOP RELOP ID NUMBER SC COM LB RB LCB RCB LSB RSB

%%
program: MAIN LB RB LCB decls stmt_list RCB
	;
decls: data_types id_list SC decls
	|
	;
data_types: INT
	| CHAR
	;
id_list: ID
	| ID COM id_list
	| ID LSB NUMBER RSB COM id_list
	| ID LSB NUMBER RSB
	;
dec_stmt: IF LB expn RB LCB stmt_list RCB dprime
	;
expn: simple_expn eprime
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
stmt_list: stmt stmt_list
	|
	;
stmt: assign_stmt SC
	| dec_stmt
	| looping_stmt
	;
assign_stmt: ID EQ expn
	;
looping_stmt: WHILE LB expn RB LCB stmt_list RCB
	| FOR LB assign_stmt SC expn SC assign_stmt RB LCB stmt_list RCB
	;
dprime: ELSE LCB stmt_list RCB
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
yyin=fopen("in.txt","r");
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
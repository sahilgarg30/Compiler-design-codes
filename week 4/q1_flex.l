%{
	#include "q1.c"
%}
%%
"#".*"\n" {}
"//".*"\n" {}
\/\*(.*\n)*.*\*\/  {};			
if|else|for|while|main|switch {printf("<%s, keyword>\n",yytext);}
[0-9]+ {printf("<%s, number>\n",yytext);}
"!"|"&&"|"&"|"\|"|"||" {printf("<%s, logical operator>\n",yytext);}
"<"|">"|"<="|">="|"=="|"!=" {printf("<%s, relational operator>\n",yytext);}
"+"|"-"|"/"|"*"|"%"|"=" {printf("<%s, arithmetic operator>\n",yytext);}
[a-z|A-Z|_][a-z|A-Z|0-9]* {}
[ \t\n]+	     /* eat up whitespace */
.	       printf( "Special character: %s\n", yytext );

%%
	int main(int argc,char *argv[])
	{
		if (argc != 2) {
		printf("Usage: ./a.out infile\n");
		exit(0);
		}
		yyin = fopen(argv[1], "r");
		yylex();

		printf("\n\n");
		fp=fopen("q4in.c","r");
		fout = fopen("output.c","w");
		col = 1;
		Initialize();
		while(getNextToken());
		printSymbolTable();
		
		return 0;
	}
	int yywrap()
	{
		return 1;
	}
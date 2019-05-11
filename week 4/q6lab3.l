%{
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
[a-z|A-Z|_][a-z|A-Z|0-9]* {printf("<%s, identifier>\n",yytext);}
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
		return 0;
	}
	int yywrap()
	{
		return 1;
	}
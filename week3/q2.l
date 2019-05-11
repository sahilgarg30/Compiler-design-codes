%{
int words = 0;
int character = 0;
int blank = 0;
int lines = 0;
%}
%%
[ ] {blank++,words++;}
[a-z] {character++;}
[\n] {words++,lines++;}
%%
	int main()
	{
		yylex();
		printf("%d %d %d %d",words,character,blank,lines);
		return 0;
	}
	int yywrap()
	{
		return 1;
	}
%{
int pn = 0;
int nn = 0;
int pf = 0;
int nf = 0;
%}
%%
[0-9]+ {pn++;}
[+][0-9]+ {pn++;}
[-][0-9]+ {nn++;}
[0-9]+[.][0-9]+ {pf++;}
[+][0-9]+[.][0-9]+ {pf++;}
[-][0-9]+[.][0-9]+ {nf++;}
%%
	int main()
	{
		yylex();
		printf("%d %d %d %d",pn,nn,pf,nf);
		return 0;
	}
	int yywrap()
	{
		return 1;
	}
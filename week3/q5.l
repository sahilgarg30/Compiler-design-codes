%{
	int simple_flag = 1;
%}
%%
(and|or|if) simple_flag = 0;
[\n] {if(simple_flag)
		printf("Simple!\n");
	else
		printf("Compound!\n");
		simple_flag = 1;
	}
[a-z] {;}
%%
int main() {
	yylex();
	return 0;
}
int yywrap() {
	return 1;
}
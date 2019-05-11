%{
int vowels = 0;
int consonants = 0;
%}
%%
[a|e|i|o|u] {vowels++;}
[b-d|f-h|j-n|p-t|v-z] {consonants++;}
%%
	int main()
	{
		yylex();
		printf("%d %d",vowels,consonants);
		return 0;
	}
	int yywrap()
	{
		return 1;
	}
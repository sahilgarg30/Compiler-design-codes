%{
	int pfc=0, sfc=0;
%}
%%
"printf" { fprintf(yyout, "WRITE"); pfc++; }
"scanf" { fprintf(yyout, "READ"); sfc++; }
%%

int main (int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: ./a.out infile outfile\n");
		exit(0);
	}
	yyin = fopen(argv[1], "r");
	yyout = fopen(argv[2], "w");
	yylex();
	printf("\nprintf = %d\n", pfc);
	printf("\nscanf = %d\n", sfc);
}

int yywrap() {
	return 1;
}
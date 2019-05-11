#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(){ 
	FILE *fa;
	int ca;
	fa = fopen("q4in.c", "r");
	if (fa == NULL){
	printf("Cannot open file \n");
	exit(0); 
	}
	int line = 1;
	ca = getc(fa);
	printf("1 : ");

	while(ca != EOF){
		if(ca == '\n'){
			line++; 
			printf("\n%d : ",line);
		}else printf("%c",ca);

		ca = getc(fa);
	}

	fclose(fa);
	return 0;
}
#include <stdio.h>
#include <stdlib.h> 
int main(){ 
	FILE *fa,*fb;
	int ca;
	fa = fopen("q4in.c", "r");
	if (fa == NULL){
	printf("Cannot open file \n");
	exit(0); 
	}
	fb = fopen("q4out.c", "w");
	ca = getc(fa);
	int col = 1;

	while(ca != EOF){
		if(ca == '#' && col == 1){
			while(ca != '\n') ca = getc(fa);
		}
		else{
			col++;
			putc(ca,fb);
		}
		if(ca == '\n') col = 1;
		if(ca != EOF) ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
}
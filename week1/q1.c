#include <stdio.h>
#include <stdlib.h>
int main(){
	FILE *fa,*fb;
	int ca;
	fa = fopen("in.txt", "r");
	if (fa == NULL){
	printf("Cannot open file \n");
	exit(0); 
	}
	fb = fopen("out.txt", "w");
	ca = getc(fa);
	while(ca != EOF){
		if(ca == '\t'){
			ca = getc(fa);
			if(ca != ' ' && ca != '\t'){putc(' ',fb);putc(ca,fb);}

		}
		else if(ca == ' '){
			ca = getc(fa);
			if(ca != ' ' && ca != '\t') {putc(' ',fb);putc(ca,fb);}
		}else{
			putc(ca,fb);
		}
		if(ca != EOF) ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);
	return 0;
}
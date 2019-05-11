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
	
	char keywords[][20] = {"int","float","double","char","switch","if","else","void","while","for"};

	char word[100];
	int line = 1;
	int coln = 0;
	int k = 0;

	ca = getc(fa);
	while(ca != EOF){
		if(ca != ' ' && ca != '\n' && ca != EOF){
			word[k++] = ca;
		}else{
			word[k] = '\0';
			for(int i=0;i<10;i++){
				if(strcmp(word,keywords[i])==0){
					for(int j=0;j<k;j++) word[j] = toupper(word[j]);
					printf("%s\t%d\t%d\n",word,line,coln-k+1);
					break;
				}
			}
			k=0;
		}
		
		if(ca == '\n'){
			line++; coln = 0;
		}else coln++;

		ca = getc(fa);
	}

	fclose(fa);
	return 0;
}
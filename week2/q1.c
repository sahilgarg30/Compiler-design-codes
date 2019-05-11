#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int row=1,col;
char ca,cb,buf[10];int i=0;
FILE *fp,*fout;

char tokenTypes[][20] = {"arithmetic operator","relational operator","logical operator","special symbol","keyword","numerical constant","identifier"};
char arop[6][3] = {"=","+","-","/","*","**"};
char reop[6][3] = {"<",">","!=","==",">=","<="};
char logop[5][3] = {"!","&&","||","&","|"};
char keywords[11][10] = {"main()","int","float","double","char","switch","if","else","void","while","for"};

int getType(char buf[],int len){
	for(int i=0;i<6;i++) if(strcmp(buf,arop[i])==0) return 0;
	for(int i=0;i<6;i++) if(strcmp(buf,reop[i])==0) return 1;
	for(int i=0;i<5;i++) if(strcmp(buf,logop[i])==0) return 2;
	for(int i=0;i<11;i++) if(strcmp(buf,keywords[i])==0) return 4;

	int i;
	for(i=0;i<len;i++) if(!isdigit(buf[i])) break;
	if(i==len) return 5;
	
	if(len>=1 && isalpha(buf[0])) return 6;

	return 3;
}

int getNextToken(){
	ca = fgetc(fp);
	if (fp == NULL){printf("Cannot open file \n");exit(0);}
	while(ca!=EOF){
		if (ca=='/'){
			cb = getc(fp);
			if (cb == '/'){
				while(ca != '\n') ca = getc(fp);
				row--;
			}
			else if (cb == '*'){
				do{
				while(ca != '*')
				ca = getc(fp);
				ca = getc(fp);
				}while (ca != '/');
				row--;
			}
			else{
				buf[i++]=ca;
				buf[i++]=cb;
				col += 2;
			}
		}
		else if(ca == '#' && col == 1){
			while(ca != '\n') ca = getc(fp);
			row--;
		}
		else if(ca=='\"'){
			buf[i++]=ca;
			ca = getc(fp);
			while(ca!='\"'){
				buf[i++]=ca;
				ca = getc(fp);
			}
			buf[i++] = '\"';
			buf[i++] = '\0';
			fprintf(fout,"<%s , %d , %d , string literal >\n",buf,row,col);
			col++;
			i=0;
			return 1;
		}
		else if(ca!=' ' && ca!='\t' && ca!='\n' && ca!=EOF){buf[i++] = ca;col++;}
		else{
			buf[i] = '\0';
			int type = getType(buf,i);
			if(strcmp(buf,"")!=0) fprintf(fout,"<%s , %d , %d , %s >\n",buf,row,col-i,tokenTypes[type]);
			if(ca=='\n'){row++;col = 1;}
			i=0;
			return 1;
		}
		if(ca == '\n'){row++;col = 1;}
		ca = fgetc(fp);
	}
	if(ca==EOF) return 0;
	return 1; 
}
int main(){
	fp=fopen("digit.c","r");
	fout = fopen("output.c","w");
	col = 1;
	while(getNextToken());
	return 0;
}
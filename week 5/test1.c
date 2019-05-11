#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char ca,cb,buf[20];int i=0;
FILE *fp;

char keywords[3][20] = {"scalar","foreach"};

typedef struct token{
	char name[20];
	char type[20];
}token;

int getType(char buf[],int len){
	for(int i=0;i<2;i++) if(strcmp(buf,keywords[i])==0) return 1;
	
	int i;
	for(i=0;i<len;i++) if(!isdigit(buf[i])) break;
	if(i==len) return 2;
	
	return 3;
}

int getNextToken(){
	ca = fgetc(fp);
	if (fp == NULL){printf("Cannot open file \n");exit(0);}
	while(ca!=EOF){
		if (ca=='#'){
			while(ca != '\n') ca = getc(fp);
		}
		else if(ca=='$'){
			buf[i++] = '$';
			ca = getc(fp);
			while(isalnum(ca)){
				buf[i++]=ca;
				ca = getc(fp);
			}
			buf[i++] = '\0';
			token t;strcpy(t.name,buf);strcpy(t.type,"identifier");
			printf("%s\t%s\n",t.name,t.type);
			i=0;
			return 1;
		}else if(ca == '+'){
			cb = getc(fp);
			if(cb == '='){
				token t;strcpy(t.name,"+=");strcpy(t.type,"special symbol");
				printf("%s\t%s\n",t.name,t.type);
				i=0;
				return 1;	
			}else{
				token t;strcpy(t.name,"+");strcpy(t.type,"operator");
				printf("%s\t%s\n",t.name,t.type);
				i=0;
				return 1;	
			}
		}else if(ca == '@'){
			cb = getc(fp);
			if(cb == '_'){
				token t;strcpy(t.name,"+=");strcpy(t.type,"special symbol");
				printf("%s\t%s\n",t.name,t.type);
				i=0;
				return 1;	
			}else{
				token t;strcpy(t.name,"@");strcpy(t.type,"OPERATOR");
				printf("%s\t%s\n",t.name,t.type);
				i=0;
				return 1;	
			}
		}
		else if(ca == '{' || ca == '}' || ca == '(' || ca == ')' || ca == '+' || ca == ';'){
			buf[0] = ca;buf[1] = '\0';
			token t;strcpy(t.name,buf);strcpy(t.type,"operator");
			printf("%s\t%s\n",t.name,t.type);
			i=0;
			return 1;	
		}
		else if(isalnum(ca)){buf[i++] = ca;}
		else{
			buf[i] = '\0';
			int type = getType(buf,i);
			if(type == 1){
				token t;strcpy(t.name,buf);strcpy(t.type,"keyword");
				printf("%s\t%s\n",t.name,t.type);
			}else if(ca == ' '){ }
			else if(i>1 && type == 2){
				token t;strcpy(t.name,buf);strcpy(t.type,"number");
				printf("%s\t%s\n",t.name,t.type);
			}
			i=0;
			return 1;
		}
		ca = fgetc(fp);
	}
	if(ca==EOF) return 0;
	return 1; 
}


int main(){
	fp=fopen("inp.c","r");
	while(getNextToken());
	return 0;
}
	
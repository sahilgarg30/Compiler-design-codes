#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define eq(x) (strcmp(l,x)==0)
#define ERROR {printf("Error");}

char input[100][100];
int datatypes[100];
int in=0;
char l[100];
char ca,cb;
FILE *fp;
char buf[100];
int i=0;
int col = 1;

char keywords[][10] = {"int","float","double","for","if","while","switch","do"};
char ops[][5] = {"{","}","(",")",";"};

int getType(char s[]){
	for(int i=0;i<8;i++) if(strcmp(keywords[i],s)==0) return 0;
	for(int i=0;i<5;i++) if(strcmp(ops[i],s)==0) return 3;
	int len = strlen(s);
	for(int i=0;i<len;i++) if(!isdigit(s[i])) return 2;
	return 1;
}

int generateTokens(){
	ca = getc(fp);
	while(ca != EOF){
		if(ca == '/'){
			cb = getc(fp);
			if(cb == '/'){
				while(ca != '\n') ca = getc(fp);
			}else if(cb == '*'){
				do{
					while(ca != '*') ca = getc(fp);
					ca = getc(fp);
				}while(ca != '/');
			}else{
				buf[i++] = ca;
				buf[i++] = cb;
				col+=2;
			}
		}else if(ca == '#' && col == 1){
			while(ca != '\n') ca = getc(fp);
		}else if(ca == '\"'){
			while(ca != '\"') ca = getc(fp);
		}
		else if(isalnum(ca) || ca == '_'){
			buf[i++] = ca;
			col++;
		}else{
			if(i==0){buf[i]=ca; buf[1] = '\0';ca = getc(fp);}
			else buf[i] = '\0';
			if(strlen(buf)>0 && strcmp(buf,"\n")!=0 && strcmp(buf," ")!=0 && strcmp(buf,"\t")!=0) {
				datatypes[in] = getType(buf);
				strcpy(input[in++],buf);
			}
			i=0;
			if(ca == '\n') col=1;
			continue;
		}

		if(ca == '\n') col = 1;
		ca = getc(fp);
	}

	return 1;
}


void getNextToken(){
	strcpy(l,input[in++]);
}

void statements(){
	getNextToken();
	if(eq("int")){
		getNextToken();
		if(datatypes[in-1]==2){
			getNextToken();
			if(eq(";"))
				statements();
			else ERROR;
		}else ERROR
	}else in--;
}

void S(){
	getNextToken();
	if(eq("int")){
		getNextToken();
		if(eq("main")){
			getNextToken();
			if(eq("(")){
				getNextToken();
				if(eq(")")){
					getNextToken();
					if(eq("{")){
						statements();
						getNextToken();
						if(!eq("}")) ERROR
					}else ERROR
				}else ERROR
			}else ERROR
		}else ERROR
	}else ERROR

	getNextToken();
	if(eq("$")) printf("Success.\n");
	else printf("Failure.\n");
}

int main(){
	fp = fopen("in3.txt","r");
	generateTokens();
	for(int i=0;i<in;i++) printf("%s - %d \n",input[i],datatypes[i]);
	in = 0;
	S();
	return 0;
}
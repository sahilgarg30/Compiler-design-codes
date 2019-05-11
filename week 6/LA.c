#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define TableLength 200

int row=1,col;
char ca,cb,buf[100];int i=0;
FILE *fp,*fout;

char keywords[10][20] = {"switch","if","else","while","for","return","statement","case","break"};
char datatypes[5][10] = {"int","float","double","char","void"};
int sizes[5] = {4,8,16,1,0};
char recDTindex = 0;
int globalScope = 1;

typedef struct token{
	char name[200];
	char type[200];
	int size;
	char scope;
	int nargs;
	char args[200];
	char returnType[100];
}token;

token curToken;

struct ListElement{
	token tok;
	struct ListElement *next;
};

struct ListElement *TABLE[TableLength];

void Initialize(){
	for(int i=0;i<TableLength;i++){TABLE[i] = NULL;}
}

int HASH(char *str){
	int x=0;
	for(int i=0;str[i]!='\0';i++) x += str[i];
	x %= TableLength;
	return x;
}

int SEARCH(char *str){
	int val = HASH(str);
	struct ListElement * ele= TABLE[val];
	while(ele!=NULL){
	if(strcmp(ele->tok.name,str)==0) break;
	ele = ele->next; // Add the element at the End in the case of a //collision.
	}
	if(ele == NULL) return 0;
	return 1;
}

void INSERT(token tk){
	if(SEARCH(tk.name)==1){return;}
	int val = HASH(tk.name);
	struct ListElement* cur = (struct ListElement*)malloc(sizeof(struct ListElement));
	cur->tok = tk;
	cur->next = NULL;
	if(TABLE[val]==NULL){
	TABLE[val] = cur; // No collosion.
	}
	else{
	struct ListElement * ele= TABLE[val];
	while(ele->next!=NULL){
	ele = ele->next; // Add the element at the End in the case of a //collision.
	}
	ele->next = cur;}
}

int getVal(char s[]){
	int res = 0;
	for(int i=0;s[i]!='\0';i++){
		res *= 10;
		res += s[i]-'0';
	}
	return res;
}

int getType(char buf[],int len){
	for(int i=0;i<9;i++) if(strcmp(buf,keywords[i])==0) return 1;
	for(int i=0;i<5;i++) if(strcmp(buf,datatypes[i])==0){
		recDTindex = i;
		return 1;
	}

	buf[len] = '\0';
	if(SEARCH(buf)){
		token te;
		strcpy(te.name,"id");
		curToken = te;
		return 7;
	}

	int i;
	for(i=0;i<len;i++) if(!isdigit(buf[i])) break;
	if(i==len) return 2;
	
	return 3;
}

int getNexttoken(){
	while(ca!=EOF){
		if(isalnum(ca) || ca == '_'){buf[i++] = ca;col++;}
		else if(i>0){
			buf[i] = '\0';
			int type = getType(buf,i);
			
			if(type == 3){
					token te;
					strcpy(te.name,buf);
					strcpy(te.returnType,"NONE");
					strcpy(te.type,datatypes[recDTindex]);
					te.size = sizes[recDTindex];
					if(globalScope) te.scope = 'G'; else te.scope = 'L';
					if(ca == '['){
						char arrsize[10]; int ai = 0;
						ca = getc(fp);
						while(ca!=']'){
							arrsize[ai++] = ca;
							ca = getc(fp);
						}
						arrsize[ai] = '\0';
						int sizeArr = getVal(arrsize);
						te.size *= sizeArr;
					}
					strcpy(te.args,"NA");
					te.nargs = 0;
					INSERT(te);
					strcpy(te.name,"id");
					curToken = te;
			}
			else if(type == 2){
				token te;
				strcpy(te.name,"num");
				curToken = te;
			}
			else if(type != 7){
				token te;
				strcpy(te.name,buf);
				curToken = te;
			}

			if(ca=='\n'){row++;col = 1;}
			i=0;
			printf("%s\n",curToken.name);
			return 1;
		}
		else if(ca=='('||ca==')'||ca=='{'||ca=='}'||ca==';'||ca=='='||ca=='$'||ca=='+'||ca=='-'||ca=='*'||ca=='/'||ca=='%'||ca=='<'||ca=='>'||ca=='!'||ca==':'){
			token te;
			buf[0]=ca;
			buf[1]='\0';
			if(ca == '<'||ca=='='||ca=='>'||ca=='!'){
				ca = fgetc(fp);
				if(ca == '='){
					buf[1] = '=';
					buf[2] = '\0';
					ca = fgetc(fp);
				}
			}
			else ca = fgetc(fp);
			strcpy(te.name,buf);
			curToken = te;
			
			printf("%s\n",curToken.name);	
			return 1;
		}

		if(ca == '\n'){row++;col = 1;}
		ca = fgetc(fp);
		
	}
	
		
	if(ca==EOF) return 0;
	return 1; 
}

void printSymbolTable(){
	printf("Name   Type   Size   Scope   Args   NArgs   ReturnType\n");
	for(int i=0;i<TableLength;i++){
		struct ListElement *e = TABLE[i];
		while(e!=NULL){
		token t = e->tok;
		printf("%s\t%s\t%d\t%c\t%s\t%d\t%s\n",t.name,t.type,t.size,t.scope,t.args,t.nargs,t.returnType);
		e = e->next;
		}
	}
}

/*
int main(){
	fp=fopen("in.c","r");
	fout = fopen("output.c","w");
	col = 1;
	Initialize();
	while(getNextToken());
	printSymbolTable();
	return 0;
}
*/	

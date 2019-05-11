#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ERROR(p) {printf("\nError %d",p);exit(0);}
#define eq(x) strcmp(l,x)

char l[100];
char input[100][30];
int in = 0;

void getNexttoken(){
	strcpy(l,input[in++]);
}

void statement_list(){
	getNexttoken();
	if(!eq("statement;")){
		statement_list();
	}
}

void assgn_stat(){
	getNexttoken();
	if(!eq("id")){
		getNexttoken();
		if(!eq("=")){
			getNexttoken();
			if(!eq("expn")){
				getNexttoken();
				return;
			}else ERROR(12);
		}else ERROR(11)
	}else ERROR(10)
}
void S(){
	getNexttoken();
	if(!eq("while")){
		getNexttoken();
		if(!eq("(")) { 
			getNexttoken();
			if(!eq("expn")){
				getNexttoken();
				if(!eq(")")){
					getNexttoken();
					if(!eq("{")){
						statement_list();
						if(eq("}")) ERROR(6)
					}else ERROR(5)
				}else ERROR(4)
			}else ERROR(3)
		}else ERROR(2)
	}

	else if(!eq("for")){
		getNexttoken();
		if(!eq("(")) { 
				assgn_stat();
				if(!eq(";")){
					getNexttoken();
					if(!eq("expn")){
						getNexttoken();
						if(!eq(";")){
								assgn_stat();
								if(!eq(")")){
									getNexttoken();
									if(!eq("{")){
									statement_list();
									if(eq("}")) ERROR(9)
									}else ERROR(8)
								}else ERROR(7)
						}else ERROR(6)
					}else ERROR(5)
				}else ERROR(4)
		}else ERROR(2)	
	}
	else ERROR(1); 
	
	getNexttoken();
	if(!eq("$")) printf("\nSuccessful");
	else ERROR(0)
}

int main(){
	char arr[100];
	int i=0;
	while(strcmp(arr,"$")!=0){
		scanf("%s",arr);
		strcpy(input[i++],arr);
	}
	S();
	return 0;
}
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

void case_stmt(){
	getNexttoken();
	if(!eq("case")){
		getNexttoken();
		if(!eq("num:")){
				statement_list();
				if(!eq("break;")){
					case_stmt();
				}else ERROR(8)				
		}else ERROR(7)
	}
}

void S(){
	getNexttoken();
	if(!eq("switch")){
		getNexttoken();
		if(!eq("(")) { 
			getNexttoken();
			if(!eq("factor")){
				getNexttoken();
				if(!eq(")")){
					getNexttoken();
					if(!eq("{")){
						case_stmt();
						if(eq("}")) ERROR(6)
					}else ERROR(5)
				}else ERROR(4)
			}else ERROR(3)
		}else ERROR(2)
	}else ERROR(1)
	
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
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ERROR {printf("\nError");exit(0);}
#define eq(x) strcmp(l,x)

char l[10];
char input[20][10];
int in = 0;

void getNexttoken(){
	strcpy(l,input[in++]);
}

void B(){
	getNexttoken();
	if(!eq("d"));
	else ERROR;
}

void A1(){
	getNexttoken();
	if(!eq("b")){
		A1();
	}else in--;
}

void A(){
	getNexttoken();
	if(!eq("b")){
		A1();
	}else ERROR
}

void S(){
	getNexttoken();
	if(!eq("a")){
		A();
		getNexttoken();
		if(!eq("c")){
			B();
			getNexttoken();
			if(!eq("e"));
			else ERROR
		}
	}

	getNexttoken();
	if(!eq("$")) printf("\nSuccess");
	else ERROR
}

int main(){
	char arr[20];
	int i=0;
	while(strcmp(arr,"$")!=0){
		scanf("%s",arr);
		strcpy(input[i++],arr);
	}
	S();
	return 0;
}

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

void Lex();

void at(){
	getNexttoken();
	if(!eq("num") || !eq("id")) return;
	else ERROR
}

void L1(){
	getNexttoken();
	if(!eq("num") || !eq("id") || !eq("(")){
		in--;
		Lex();
		L1();
	}else{
		in--;
	}
}

void lseq(){
	Lex();
	L1();
}

void li(){
	getNexttoken();
	if(!eq("(")){
		lseq();
		getNexttoken();
		if(!eq(")"));
		else ERROR
	}else ERROR
}

void Lex(){
	if(strcmp(input[in],"(")==0){
		li();
		getNexttoken();
		if(!eq("$")) {printf("\nSuccess");return;}
		else {in--;return;}
	}
	else{
		at();
		getNexttoken();
		if(!eq("$")) {printf("\nSuccess");return;}
		else {in--;return;}
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
	Lex();
	return 0;
}

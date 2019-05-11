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

void S();
void T2(){
	if(!eq(",")){
		S();
		T2();
	}
}

void T(){
	S();
	T2();
}

void S(){
	getNexttoken();
	if(!eq("a") || !eq(">")){
		getNexttoken();
		if(!eq("$")) {printf("\nSuccessful");return;}
		else return;
	}
	else if(!eq("(")){
		T();
		getNexttoken();
		if(!eq(")"));
		else ERROR
	}

	getNexttoken();
	if(!eq("$")) printf("\nSuccessful");
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

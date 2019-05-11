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

void E();
void F(){
	getNexttoken();
	if(!eq("(")){
		E();
		getNexttoken();
		if(!eq(")"));
		else ERROR
	}
	else if(!eq("id"));
	else ERROR

}

void T1(){
	getNexttoken();
	if(!eq("*")){
		F();
		T1();
	}else in--;
}

void T(){
	F();
	T1();
}

void E1(){
	getNexttoken();
	if(!eq("+")){
		T();
		E1();
	}else in--;
}

void E(){
	T();
	E1();

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
	E();
	return 0;
}

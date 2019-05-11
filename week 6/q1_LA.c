#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "LA.c"
#define ERROR(p) {printf("\nError %d",p);exit(0);}
#define eq(x) strcmp(curToken.name,x)

void factor(){
	if(eq("id") && eq("num")) ERROR(13)
}

void tprime(){
	if(eq("*") && eq("/") && eq("%")) return;
	getNexttoken();
	factor();
	getNexttoken();
	tprime();
}

void term(){
	factor();
	getNexttoken();
	tprime();
}

void seprime(){
	if(eq("+") && eq("-")) return;
	getNexttoken();
	term();
	seprime();	
}

void simpleexpn(){
	term();
	seprime();
}

void eprime(){
	if(eq("==") && eq("!=") && eq("<=") && eq(">=") && eq(">") && eq("<")) return;
	getNexttoken();
	simpleexpn();
}

void expn(){
	getNexttoken();
	simpleexpn();
	eprime();	
}

void statement_list(){
	getNexttoken();
	if(!eq("statement")){
		getNexttoken();
		if(!eq(";")){
		statement_list();
		}else ERROR(200)
	}	
}

void case_stmt(){
	getNexttoken();
	if(!eq("case")){
		getNexttoken();
		if(!eq("num")){
			getNexttoken();
			if(!eq(":")){
				statement_list();
				if(!eq("break")){
					getNexttoken();
					if(!eq(";")){
					case_stmt();}else ERROR(9)
				}else ERROR(8)
			}else ERROR(7)				
		}else ERROR(6)
	}
}

void S(){
	getNexttoken();
	if(!eq("switch")){
		getNexttoken();
		if(!eq("(")) { 
			expn();
				if(!eq(")")){
					getNexttoken();
					if(!eq("{")){
						case_stmt();
						if(eq("}")) ERROR(6)
					}else ERROR(5)
				}else ERROR(4)
		}else ERROR(2)
	}else ERROR(1)
	
	getNexttoken();
	if(!eq("$")) printf("\nSuccessful");
	else ERROR(0)
}

int main(){
	fp=fopen("in2.c","r");
	col = 1;
	Initialize();
	S();
	printSymbolTable();
	return 0;
}
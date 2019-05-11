#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "LA.c"
#define ERROR(p) {printf("\nError %d\n",p);exit(0);}
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

void assgn_stat(){
	getNexttoken();
	if(!eq("id")){
		getNexttoken();
		if(!eq("=")){
			expn();
		}else ERROR(11)
	}else ERROR(10)
}

void S(){
	getNexttoken();
	if(!eq("while")){
		getNexttoken();
		if(!eq("(")) { 
			expn();
				if(!eq(")")){
					getNexttoken();
					if(!eq("{")){
						statement_list();
						if(eq("}")) ERROR(6)
					}else ERROR(5)
				}else ERROR(4)
		}else ERROR(2)
	}

	else if(!eq("for")){
		getNexttoken();
		if(!eq("(")) { 
				assgn_stat();
				if(!eq(";")){
						expn();
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
				}else ERROR(4)
		}else ERROR(2)	
	}
	else ERROR(1); 
	
	getNexttoken();
	if(!eq("$")) printf("\nSuccessful\n");
	else ERROR(0)
}

int main(){
	fp=fopen("in.c","r");
	col = 1;
	Initialize();
	S();
	printSymbolTable();
	return 0;
}
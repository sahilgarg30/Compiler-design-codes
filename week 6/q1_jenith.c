/*
Recursive descent parser for looping statements

looping-stat -> while (expn) {statement_list} | for (assign_stat ; expn ; assign_stat ) {statement_list}

expn -> simple-expn eprime
simple-exp -> term seprime
eprime -> relop simple-expn| epsilon
seprime -> addop term seprime | epsilon
term -> factor tprime
tprime -> mulop factor tprime | epsilon
factor -> id|num
relop -> == | != |<= | >= | > |<
addop -> + | -
mulop ->*|/ |%

statement_list -> statement statement_list | epsilon
statement -> assign-stat; | decision_stat | looping-stat
assign_stat -> id = expn
decision-stat -> if ( expn ) {statement_list} dprime
dprime -> else {statement_list} | epsilon
*/

#include <stdio.h>
#include <string.h>
#define error(x) {printf("String rejected %d Counter value %d\n",x,counter);}
char input[10][20];
int ind=0, counter=0;
void statement_list(){
	if(strcmp(input[++counter],"id")==0 || strcmp(input[counter],"num")==0 ||strcmp(input[counter],"if")==0 || strcmp(input[counter],"while")==0 || strcmp(input[counter],"for")==0){
	statement();
	statement_list();
	}
	else 
		counter--;
}
void statement(){
	if(strcmp(input[counter],"id")==0 || strcmp(input[counter],"num")==0)
		assign_stat();
	else if(strcmp(input[counter],"if")==0)
		decision_stat();
	else
		loop();
}
void assign_stat(){
	if(strcmp(input[++counter],"=")==0){
		expn();
		if(strcmp(input[++counter],";")==0 || strcmp(input[counter],")")==0){}
		else error(9);
	}
	else
		error(8);
}
void decision_stat(){
	if(strcmp(input[++counter],"(")==0){
		expn();
		if(strcmp(input[++counter],")")==0){
			if(strcmp(input[++counter],"{")==0){
				statement_list();
				if(strcmp(input[++counter],"}")==0){}
				else error(12);
				dprime();
			}else error(11);
			
		}
		else error(10);
	}
}
void dprime(){
	if(strcmp(input[++counter],"else")==0){
		if(strcmp(input[++counter],"{")==0){
			statement_list();	
			if(strcmp(input[++counter],"}")==0){}
			else error(14);
		}
		else error(13);
	}
	return;
}
void getwords(char str[]){
	char buf[10];
	int i=0,j=0;
	for(i=0;str[i]!='\0';i++){
		if(str[i] == ' '){
			buf[j] = '\0';
			strcpy(input[ind++],buf);
			j=0;
		}
		else{
			buf[j++] = str[i];
		}
	}
	buf[j++] = '\0';
	strcpy(input[ind++],buf);
}
void expn(){
	simple_expn();	
	eprime();
}
void eprime(){
	if(strcmp(input[++counter],"==")==0 ||strcmp(input[counter],"!=")==0 ||strcmp(input[counter],"<=")==0 ||strcmp(input[counter],">=")==0 ||strcmp(input[counter],">")==0 ||strcmp(input[counter],"<")==0 )
		simple_expn();
	else
		counter--;
}
void simple_expn(){
	term();
	seprime();
}
void seprime(){
	if(strcmp(input[++counter],"+")==0 ||strcmp(input[counter],"-")==0){
		term();
		seprime();
	}
	else
		counter--;
}
void term(){
	if( strcmp(input[++counter],"id")==0 || strcmp(input[counter],"num") == 0){}
	else
		error(1);
	tprime();
}
void tprime(){
	if(strcmp(input[++counter],"*")==0 || strcmp(input[counter],"/")==0 ||strcmp(input[counter],"%")==0 ){
		if( strcmp(input[++counter],"id")==0 || strcmp(input[counter],"num") == 0){
			tprime();	
		}
		else
			error(4);		
	}
	else{
		counter--;	
		return;
	}
}
void loop(){
	char next[10];
	if(strcmp(input[counter],"while")==0){
		if(strcmp(input[++counter],"(") == 0){
			expn();
			if(strcmp(input[++counter],")")==0){
				if(strcmp(input[++counter],"{")==0){
					statement_list();
					if(strcmp(input[++counter],"}")==0){
						printf("Statement is accepted");
					}
					else error(15);
				}
				else
					error(7);
			}
			else
				error(6);
		}
		else
			error(2);
	}
	else if(strcmp(input[counter],"for")==0){
		if(strcmp(input[++counter],"(")==0){
			if(strcmp(input[++counter],"id")==0 || strcmp(input[counter],"num")==0){
			assign_stat();	
			expn();
			if(strcmp(input[++counter],";")==0){
				if(strcmp(input[++counter],"id")==0 || strcmp(input[counter],"num")==0){
					assign_stat();
					if(strcmp(input[++counter],"{")==0)
						statement_list();
					else error(19);
					if(strcmp(input[++counter],"}")==0)
						printf("Statement accepted\n");
				}
			}
			else error(17);
		}
	}
	else error(16);
}
}
int main(){
	printf("Enter a statement: ");
	char in[100];
	gets(in);
	getwords(in);
	loop();
}

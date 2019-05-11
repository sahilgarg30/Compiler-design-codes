#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

char lookahead[10];
char input[20][10];
int in = 0;

void getNexttoken(){
	strcpy(lookahead,input[in++]);
}

int i=0;
void proc_t();
void proc_e()
{
getNexttoken();
if(strcmp(lookahead,"NUM")==0)
{
proc_t();
}
else
{
printf("\nError");
}
if(strcmp(lookahead,"$")==0)
printf("\nSuccessful");
else
printf("\nError");
}
void proc_t()
{
getNexttoken();
if(strcmp(lookahead,"MUL")==0)
{
getNexttoken();
if(strcmp(lookahead,"NUM")==0)
{
proc_t();}
else{
	printf("\nError"); exit(0);
}
} }
int main()
{
char arr[20] = "";
int i=0;
while(strcmp(arr,"$")!=0){
	scanf("%s",arr);
	strcpy(input[i++],arr);
}
proc_e();
return 0;
}

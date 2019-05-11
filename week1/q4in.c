// This is a single line comment
/* *****This is a
******Multiline Comment
**** */
#include <stdio.h>
void main()
{
FILE *fopen(), *fp;
int c ;
fp = fopen( “prog.c”, “r” ); //Comment
c = getc( fp ) ;
//#include <stdio.h>
while ( c
!=
EOF )
{
printf("#include <stdio.h>");
putchar( c ); int x;
c = getc ( fp );
}
/*multiline
comment */
fclose(
fp );
}

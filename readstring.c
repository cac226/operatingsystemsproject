#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int main () {
	printf("enter sentance: ");
	char str[80];
	scanf("%s", str);
	const char s[2] = " ";
	char *token;
   
	/* get the first token */
	token = strtok(str, s);
   
	/* walk through other tokens */
	while( token != NULL ) {
		printf( " %s l\n", token ); 
		token = strtok(NULL, s);
	}
   
	return(0);
}
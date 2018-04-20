#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

int main () {
	printf("enter sentance: ");
	char str[80];
	fgets(str  ,20,stdin);
	const char s[2] = " ";
	char *token;	
	int con;
   
	/* get the first token */
	token = strtok(str, s);
   
	/* walk through other tokens */
	while( token != NULL ) {
		if (isdigit(*token)){
			con = *token - '0';
			printf("%d-digit",con);
			if (con <= 9 && con >= 0)
				printf("yes\n");
		}
		else
			printf("no");
		token = strtok(NULL, s);
	}
   
	return(0);
}
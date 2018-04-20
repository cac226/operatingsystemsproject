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
	printf("%s", str);
	
	return 0;
}
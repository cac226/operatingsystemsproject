#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main() {
	int i = 0;
   	int d[4] = {0, 1, 2, 5};
	for(i = 0; i < sizeof(d)/sizeof(d[0]); i++)
		printf("val = %d", d[i]);

}
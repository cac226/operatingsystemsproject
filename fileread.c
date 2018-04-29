// Caitlin Campbell and Shanti Polara Final Project
//Beta version
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[]){
		//pointer to file
	FILE *file;
	//checks if correct size of input has been entered
	if (argc == 0){
		printf("Error: wrong number of arguments\n"
				"please enter the name of the text file containing the data\n");
	}
	printf("argc: %d\n", argc);
	
	if ((file = fopen(argv[1], "r"))==NULL) {
		printf("Cannot open file \n");
		exit(1);
	}
	//data = malloc(sizeof(data)/sizeof(data[0]));
	char str[10];
	int i = 0;
	int nch = 0;
	double con = 0;
	int badinput = 0;
	int size = 10;
	double *data = malloc(size);
	
	while (fscanf(file, "%s", str) == 1){
		if (i >= size - 1){
			size = size + 10;
			data = realloc(data, size * sizeof(con));
			if(data == NULL){
				fprintf(stderr, "out of memory\n");
				exit(1);
            }
		}
		if(isdigit(*str)){
			con = atoi(str);
			data[i] = (double)con;
			i++;
			printf("int = %.2f\n", data[i]);
		}
		else{
			badinput = 1;
		}
	}
	for(i = 0; i < sizeof(data)/sizeof(data[0]); i++)
		printf("val = %.2f\n", data[i]);

	return 0;
}
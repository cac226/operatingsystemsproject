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
	if (argc == 0 || argc > 1){
		printf("Error: wrong number of arguments\n"
				"please enter the name of the text file containing the data\n");
	}
	
	if ((file = fopen(argv[1], "r"))==NULL) {
		printf("Cannot open file \n");
		exit(1);
	}
	double *data;
	data = malloc(sizeof(data)/sizeof(data[0]));
	char str[30];
	int i = 0;
	int con;
	int badinput = 0;
	while (fscanf(file, "%s", str)!=EOF){
		if (isdigit(str)){
			con = str - '0';
			data[i] = con;
		}
		else
			badinput = 1;
	}
	if(badinput)
		printf("bad input");

	return 0;
}
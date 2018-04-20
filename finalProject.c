// Caitlin Campbell and Shanti Polara Final Project
//Beta version

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>

/*in order for the threads to function, they must be joined all at once, but called 
one by one, they should have seperate variables they modify*/
double mean(double data[]);
double * sort(double data[]);
double * minMedMax(double data[]); //returns array of min, median, and max
double * quartile(double data[]); //returns
double sd(double data[]);

int main (){
    /*
     PLAN: by default, will return everything, if give input, then will only do some things
     */
	 //data from file must be stored into array called data 
	double data[10]; /* this is a temperary file for the data that will be given
	 the values from the input file*/
	char line[50];
	char *args[30];
	int i = 0;
	int ops[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int badinput = 0;
	int holder = 0;
	char hold;
	int threadcount = 0;
	int iterator;
	//printf("here1\n");
	fflush(stdout);
	//defines data that methods will return
	double mean, sd;
	//double sort[(sizeof(data)/sizeof(data[0]))], minMedmax[3], quartile[2]; 
	printf("Choose one or more of the following operations on the data by\n"
			"typing the coresponding number(s) seperated by a space\n"
			"0)all options \n1)Mean \n2)Median \n3)Mode \n4)Standard Deviation \n5)Maximum Value"
			"\n6)Minimum Value \n7)Sorted List \n8)First Quartile \n9)Third Quartile\n");
	scanf("%d", &line);
	for (i=0; i < 50; i++)
		printf(line[i]);
	
	args[0] = strtok(line, " ");
	//printf("here2\n");
	while (args[i] != NULL){
		args[i] = strtok(NULL, " ");
		hold = args[i];
		printf("%s", hold);
		if(isdigit(args[i])){ 
			printf("yay\n");
		}
		i++;
	}
	//printf("here3\n");
	fflush(stdout);
	iterator = sizeof(args) - sizeof(args[0]);
	i = 1;
	/*
	while(iterator > 0){ 
		if(isdigit(args[i])){ //checks if input valid
			holder = args[i];
			if (holder <= 9 && holder >= 0) //lets program know what operations are desired
				ops[holder] = 1;
			else
				badinput = 1;
		}
		iterator = iterator - sizeof(args[i]);
		i++;
	}*/
	printf("here1\n");
	if (badinput){
		printf("Error: Bad input\n");
		return -1;
	}
	if (ops[0]){
		for (i = 1; i < sizeof(ops); i++)
			ops[i] = 1;
	}
	printf("here3\n");
	if (ops[1]){ //mean
		printf("mean\n");
	}
	
	if ((ops[2] || ops[5]) || ops[6]){ //median, max, min
		
		if (ops[2])//median
			printf("median\n");
		if (ops[6]) //minumum
			printf("minimum\n");
		if (ops[5])//maximum
			printf("maximum\n");	
	}
	
	if (ops[3]){ //mode
		printf("mode\n");
	}
	
	if (ops[4]){ //standard deviation
		printf("standard dev\n");
	}
	
	if (ops[7]){ //sorted list
		double list[3] = {1.0, 2.0, 3.0};
		for (i = 0; i < sizeof(list); i++){//replace with data set when sort method ready
			printf("%.2f ", list[i]);
		}
	}
	
	if (ops[8] || ops[9]){ //first quartile, second quartile
		if(ops[8]){
			printf("first quartile\n");
		}
		
		if(ops[9]){
			printf("second quartile\n");
		}
	}
		
	return 0;
	
	
	
}

//returns the mean
double mean(double data[]) {
    int numOfData = (sizeof(data)/sizeof(data[0]));
    int sum = 0;
    int i;
    for(i = 0; i < numOfData; i++) {
        sum += data[i];
    }
    return sum / numOfData;
    return 0;
}

//quicksort method
double * quicksort(double data[]) {
    double sorted[(sizeof(data)/sizeof(data[0]))];
    
    
    return sorted;
}
	
double * sort(double data[]) {
    return data;
}

//assumes data is sorted
double median(double data[]) {
    
	if((sizeof(data)/sizeof(data[0])) % 2 == 1) { //data size is odd
        return data[((sizeof(data)/sizeof(data[0])) - 1) / 2];
    }
    double val1 = data[(sizeof(data)/sizeof(data[0])) / 2]; //first middle value
    double val2 = data[((sizeof(data)/sizeof(data[0])) - 2) / 2]; //second middle value
    
    return (val1 + val2) / 2;
}

double * minMedMax(double data[]) { //returns array of min, median, and max
    return data;
}

//assumes data is sorted
//returns values that make quartiles
double * quartile(double data[]) {
    
    return 0;
}


double sd(double data[]) {
    return 0;
}
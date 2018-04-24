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

/*in order for the threads to function, they must be joined all at once, but called 
one by one, they should have seperate variables they modify*/
double mean(double data[]);
double sort(double data[]);
double minMedMax(double data[]); //returns array of min, median, and max
double quartile(double data[]); //returns
double sd(double data[]);
double mode(double data[]);


double quartileData[2];
double mean, sd, min, median, max;
double *sortedData[];

int main(int argc, char *argv[]){
    /*
     PLAN: by default, will return everything, if give input, then will only do some things
     */
	 //data from file must be stored into array called data 
	double data[10] = {1,3,4,55,6,21,4,5,7,10}; /* this is a temperary file for the data that will be given
	 the values from the input file*/
	//recives user input
	char line[20];
	//tokenizes input into an array
	char *token;
	//counter value
	int con, i = 0;
	//keeps track of requested operations on the data using 0, 1 as boolean values
	int ops[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//keeps track of if user inputs non-numbers
	int badinput = 0;
	//keeps track of how many threads are being used
	int threadcount = 0;
	/* set of attributes for the thread */
	pthread_attr_t attr; 
	/* get the default attributes */
	pthread_attr_init(&attr);
	//defines data that methods will return
	double mean, sd;
	//alocating size of sortedData to be size of input data
	sortedData = malloc(sizeof(data)/sizeof(data[0]));
	//pointer to file
	FILE *fp;
	//checks if correct size of input has been entered
	if (argc == 0 || argc > 1){
		printf("Error: wrong number of arguments\n"
				"please enter the name of the text file containing the data\n");
	}
	
	if ((fp = fopen(argv[1], "r"))==NULL) {
		printf("Cannot open file \n");
		exit(1);
	}
	
	
	
	//double sort[(sizeof(data)/sizeof(data[0]))], minMedmax[3], quartile[2]; 
	printf("Choose one or more of the following operations on the data by\n"
			"typing the corresponding number(s) separated by a space\n"
			"0)all options \n1)Mean \n2)Median \n3)Mode \n4)Standard Deviation \n5)Maximum Value"
			"\n6)Minimum Value \n7)Sorted List \n8)First Quartile \n9)Third Quartile\n");
	fgets(line, 20, stdin);
	token = strtok(line, " ");
	//reading in string, making sure only numbers were entered
	while(token != NULL ) {
		if (isdigit(*token)){
			con = *token - '0';
			fflush(stdout);
			if (con <= 9 && con >= 0)
				ops[con] = 1;
			else
				badinput = 1;
		}
		else
			badinput = 1;
		token = strtok(NULL, " ");
	}

	//initialize thread ids
	pthread_t tid[6]; 
	
	//error message if non-numbers were entered
	if (badinput){
		printf("Error: Bad input, you have not entered your request in the correct format\n");
		return -1;
	}
		
	//if user requests all operations, set all operations to true
	if (ops[0]){
		for (i = 1; i < sizeof(ops)/sizeof(ops[0]); i++)
			ops[i] = 1;
	}
	
	//checks if user is requesting any operations that use a sorted list
	if (ops[7] || ops[2] || ops[5] || ops[6] || ops[3] || ops[8] || ops[9]){ 
		//test code
		double list[3] = {1.0, 2.0, 3.0};
		for (i = 0; i < sizeof(list)/sizeof(list[0]); i++){
			printf("%.2f ", list[i]);
		}
		for (i = 0; i < sizeof(data)/sizeof(data[0]); i++){
			data[i] = sortedData[i];
		}
		
		//sort has to sort the data before any of the methods that require sorted data run
		pthread_create(&tid[6], &attr, *sort, &data);
		pthread_join(tid[6], NULL);
		
	}
	
	int j = 0;
	//thread creation for mean, keeping track of number of threads
	if (ops[1]){ //mean
		pthread_create(&tid[j], &attr, mean, &data);
		threadcount++;
		j++;
	}
	 
	//checks if user requested median, max or min as operations
	if ((ops[2] || ops[5]) || ops[6]){ //median, max, min
		
		if (ops[2])//median
			printf("median\n");
		if (ops[6]) //minumum
			printf("minimum\n");
		if (ops[5])//maximum
			printf("maximum\n");
		pthread_create(&tid[j], &attr, NULL, data);
		threadcount++;	
		j++;
	}
	
	//checks if user requested mode as an operation
	if (ops[3]){ 
		printf("mode\n");
		pthread_create(&tid[j], &attr, mode, &data);
		threadcount++;	
		j++;
	}
	
	//checks if user requested standard deviation as an operation
	if (ops[4]){ 
		printf("standard dev\n");
		pthread_create(&tid[j], &attr, sd, &data);
		threadcount++;	
		j++;
	}
	

	//checks if user requested first quartile or second quartiles as operations
	if (ops[8] || ops[9]){ 
		//first quartile
		if(ops[8]){
			printf("first quartile\n");
		}
		//second quartile
		if(ops[9]){
			printf("second quartile\n");
		}
		pthread_create(&tid[j], &attr, quartile, &data);
		threadcount++;
		j++;
	}
		
	for (i = 0; i < threadcount; i++)
		pthread_join(tid[i], NULL);
	
	//print statements for results
	if(ops[1])
		printf("Mean = %.2f\n", mean);
	if(ops[2])
		printf("Median = %.2f\n", median);
	if(ops[3])
		printf("Mode = %.2f\n", mode);
	if(ops[4])
		printf("Standard Deviation = %.2f\n", sd);
	if(ops[5])
		printf("Maximum Value = %.2f\n", max;
	if(ops[6])
		printf("Minimum Value = %.2f\n", min);
	if(ops[8])
		printf("First Quartile = %.2f\n", quartileData[0]);
	if(ops[9])
		printf("Third Quartile = %.2f\n", quartileData[1]);
	
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
}
               
//returns sorted list of data
double sort(double data[]) {
    int dataSize = (sizeof(data)/sizeof(data[0]));
    double result[dataSize];
    
    
    
    sortedData = result;
    return 0;
}

//indexes: min = 0, med = 1, max =2
//finds the minimum, median and max of the data
double minMedMax(double data[]) { //returns array of min, median, and max
    //number of elements in the data set
    int dataSize = sizeof(data)/sizeof(data[0]);
    
    if(dataSize % 2 == 1) { //data size is odd
        median = data[(dataSize - 1) / 2];
    } else { //data size is even
        double val1 = data[dataSize / 2]; //first middle value
        double val2 = data[(dataSize - 2) / 2]; //second middle value
        median = (val1 + val2) / 2;
    }
    
    min = data[0];
    max = data[dataSize];
    
}

//assumes data is sorted
//returns values that make quartiles
//quartile data index: 0 is first quartile, 1 is second quartile
double quartile(double data[]) {
    //method does not need to return anything, results should be assined to quartileData
    //quartileData[0]=
	//quartileData[1]=
    return 0;
	
}

//returns the standard deviation of the data
double sd(double data[]) {
    return 0;
}

//returns the mode of the data
//assumes data is sorted
double mode(double data[]){
    //TODO: Make so can account for either multiple modes, or no modes
    int dataSize = sizeof(data)/sizeof(data[0]);
    double EPSILON = 0.000001; //for purposes of comparing doubles
    
    double currentMode = data[0];
    int maxTimesOccured = 1;
    int i = 0;
    while(i < dataSize && (Math.abs(data[i] - currentMode) < EPSILON)) {
        maxTimesOccured++;
        i++;
    }
    double beingChecked = data[i];
    i++;
    int timesOccured = 1;
    while(i < dataSize) {
        if(Math.abs(data[i] - beingChecked) < EPSILON) { //if found another instance
            timesOccured++;
        } else {
            if(timesOccured > maxTimesOccured) {
                maxTimesOccured = timesOccured;
                currentMode = beingChecked;
            }
            
            beingChecked = data[i];
            timesOccured = 1;
        }
        i++;
    }
    
    mode = currentMode;
	return 0;
}

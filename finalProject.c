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

/*in order for the threads to function, they must be joined all at once, but called 
one by one, they should have seperate variables they modify*/
double mean(double data[]);
double * sort(double data[]);
double * minMedMax(double data[]); //returns array of min, median, and max
double * quartile(double data[]); //returns

double sd(double data[]);
double minMedmax[3], quartile[2];
int main (){
    /*
     PLAN: by default, will return everything, if give input, then will only do some things
     */
	 //data from file must be stored into array called data 
	double data[10] = {1,3,4,55,6,21,4,5,7,10} /* this is a temperary file for the data that will be given
	 the values from the input file*/
	char line[20];
	char *token;
	int i = 0;
	int ops[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int badinput = 0;
	int threadcount = 0;
	int con;
	//printf("here1\n");
	fflush(stdout);
	//defines data that methods will return
	double mean, sd;
	double sort[(sizeof(data)/sizeof(data[0]))];
	//double sort[(sizeof(data)/sizeof(data[0]))], minMedmax[3], quartile[2]; 
	printf("Choose one or more of the following operations on the data by\n"
			"typing the coresponding number(s) seperated by a space\n"
			"0)all options \n1)Mean \n2)Median \n3)Mode \n4)Standard Deviation \n5)Maximum Value"
			"\n6)Minimum Value \n7)Sorted List \n8)First Quartile \n9)Third Quartile\n");
	fgets(line, 20, stdin);
	printf("%s-line", line);
	token = strtok(line, " ");
	//reading in string, making sure only numbers were entered
	while(token != NULL ) {
		if (isdigit(*token)){
			con = *token - '0';
			fflush(stdout);
			if (con <= 9 && con >= 0)
				ops[con] = 1;
		}
		else
			badinput = 1;
		token = strtok(NULL, " ");
	}

	//initialize thread ids, can have up to 6 threads, so prepair 6 tids
	pthread_t tid[6]; 
	
	//error message if non-numbers were entered
	if (badinput){
		printf("Error: Bad input\n");
		return -1;
	}
		
	//if user requests all operations, set all operations to true
	if (ops[0]){
		for (i = 1; i < sizeof(ops)/sizeof(ops[0]); i++)
			ops[i] = 1;
	}
	
	//begin thread creation, keeping track of number of threads
	if (ops[1]){ //mean
		pthread_create(&tid[1], mean, mean, data);
		threadcount++;
	}
	
	if ((ops[2] || ops[5]) || ops[6]){ //median, max, min
		
		if (ops[2])//median
			printf("median\n");
		if (ops[6]) //minumum
			printf("minimum\n");
		if (ops[5])//maximum
			printf("maximum\n");
		//pthread_create(&tid[2], NULL, minmedmax, data);
		//threadcount++;			
	}
	
	if (ops[3]){ //mode
		printf("mode\n");
	}
	
	if (ops[4]){ //standard deviation
		printf("standard dev\n");
	}
	
	if (ops[7]){ //sorted list
		double list[3] = {1.0, 2.0, 3.0};
		for (i = 0; i < sizeof(list)/sizeof(list[0]); i++){//replace with data set when sort method ready
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
		
	for (i = 0; i < threadcount; i++)
		pthread_join(tid[i], NULL);
	
	//print statements for results
	if(ops[1])
		printf("Mean = %.2f\n", mean);
	if(ops[2])
		printf("Median = %.2f\n", minMedmax[1]);
	if(ops[3])
		printf("Mode = %.2f\n", mode);
	if(ops[4])
		printf("Standard Deviation = %.2f\n", sd);
	if(ops[5])
		printf("Maximum Value = %.2f\n", minMedmax[2]);
	if(ops[6])
		printf("Minimum Value = %.2f\n", minMedmax[0]);
	if(ops[8])
		printf("First Quartile = %.2f\n", quartile[0]);
	if(ops[9])
		printf(	
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

//quicksort method
double * mergesort(double data[]) {
    //number of elements in the data set
    int dataSize = sizeof(data)/sizeof(data[0]);
    
    //recursion step
    if(dataSize < 2) {
        return data[];
    }
    
    double firstHalf[];
    double secondHalf[];
    
    
    
    return(mergesort(merge(firstHalf), merge(secondHalf)));
}

double * merge(double firstHalf[], double secondHalf[]) {
    int i = 0;
    int j = 0;
    int firstSize  = sizeof(firstHalf)/sizeof(firstHalf[0]);
    int secondSize = sizeof(secondHalf)/sizeof(secondHalf[0]);
    double result[firstSize + secondSize];
    
    while(i < firstSize && j < secondSize) {
        if(firstHalf[i] < secondHalf[j]) {
            //i element is smaller
            result[i + j] = firstHalf[i];
            i++;
        } else {
            //j element is smaller
            result[i + j] = secondHalf[j];
            j++;
        }
    }
    
    //if there's still some left in the first half
    while(i < firstSize) {
        result[i + j] = firstHalf[i];
        i++;
    }
    
    //if there's still some left in the second half
    while(j < secondSize) {
        result[i + j] = secondHalf[j];
        j++;
    }
    
    return result;
}
	
double * sort(double data[]) {
    return data;
}


//assumes data is sorted
double median(double data[]) {
    //number of elements in the data set
    int dataSize = sizeof(data)/sizeof(data[0]);
    
	if(dataSize % 2 == 1) { //data size is odd
        return data[(dataSize - 1) / 2];
    }
    double val1 = data[dataSize / 2]; //first middle value
    double val2 = data[(dataSize - 2) / 2]; //second middle value
    
    return (val1 + val2) / 2;
}

//indexes:min = 0, med = 1, med =2
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

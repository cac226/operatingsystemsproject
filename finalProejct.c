// Caitlin Campbell and Shanti Polara Final Project
//Beta version
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For wait()


double mean(double[] data);
double[] quicksort(double[] data);
double median(double[] data); //median
double quartile(double[] data); //returns
double sd(double[] data);
double mode(double[] data);

int main (){
    /*
     PLAN: by default, will return everything, if give input, then will only do some things
     */
	printf("Please choose what operations you wish to occur ");
	gets(line);
	args[0] = strtok(line, " ");
	while (args[i] != NULL){
		args[++i] = strtok(NULL, " ");
	}
	
}

//returns the mean
double mean(double[] data) {
    int numOfData = data.sizeof;
    int sum = 0;
    int i;
    for(i = 0; i < numOfData; i++) {
        sum += data[i];
    }
    return sum / numOfData;
}

//quicksort method
double[] quicksort(double[] data) {
    double sorted[data.sizeof];
    
    
    return sorted;
}

//assumes data is sorted
double median(double[] data) {
    if(data.sizeof % 2 == 1) { //data size is odd
        return data[(data.sizeof - 1) / 2];
    }
    double val1 = data[data.sizeof / 2]; //first middle value
    double val2 = data[(data.sizeof - 2) / 2]; //second middle value
    
    return (val1 + val2) / 2;
}

//assumes data is sorted
//returns values that make quartiles
double quartile(double[] data) {
    
}

double sd(double[] data) {
    return 0;
}

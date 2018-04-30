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
#include <pthread.h>

//struct for data
typedef struct myData {
    double *data;
    int size;
};

/*in order for the threads to function, they must be joined all at once, but called
 one by one, they should have seperate variables they modify*/
double mean(double data[]);
void sort(double data[]);
void minMedMax(double data[]); //returns array of min, median, and max
void quartile(double data[]); //returns
void sd(double data[]);
void mode(double data[]);

double quartileData[2];
double meanVal, standardDeviation, min, median, max, globMode;
double *sortedData;

int main(int argc, char *argv[]){
    
    pthread_attr_t attr; // set of attributes for the thread
    pthread_attr_init(&attr); // get the default attributes
    
<<<<<<< HEAD
    double data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    double meanVal, standardDeviation; //defines data that methods will return
    double sortedData[10]; //alocating size of sortedData to be size of input data
    double meanResult;
    //initialize thread ids
    pthread_t tid[6];
=======
    /*
     PLAN: by default, will return everything, if give input, then will only do some things
     */
	 //data from file must be stored into array called data 
	double data[6] = {1, 2, 3, 4, 5, 6};
    
    struct myData mainData;
    mainData.size = (sizeof(data)/sizeof(data[0]));
    mainData.data = data;
	int threadcount = 6;
	/* set of attributes for the thread */
	pthread_attr_t attr; 
	/* get the default attributes */
	pthread_attr_init(&attr);
	//defines data that methods will return
	double meanVal, standardDeviation;
	//alocating size of sortedData to be size of input data
	sortedData = malloc(sizeof(data)/sizeof(data[0]));
	//pointer to file

	//initialize thread ids
	pthread_t tid[6];
    
    pthread_create(&tid[0], &attr, quartile, &mainData);
    pthread_join(tid[0], NULL);
>>>>>>> parent of b8a23d4... testing
    
    pthread_create(&tid[5], &attr, mean, &data);
    pthread_join(tid[5], &meanResult);
    
    printf("\nMean: %.2f", meanResult);
    
}


//returns the mean
double mean(double data[]) {
    int numOfData = (sizeof(data)/sizeof(data[0]));
    double sum = 0;
    int i;
    for(i = 0; i < numOfData; i++) {
        sum += data[i];
    }
    double temp = (sum / numOfData);
    printf("Mean thing says: %.2f\n\nSum: %.2f\nSize: %.2f", temp, sum, numOfData);
    //meanVal = myMean;
    //pthread_exit(&myMean);
    return temp;
}

//returns sorted list of data
void sort(double data[]) {
    int dataSize = (sizeof(data)/sizeof(data[0]));
    
    double result[dataSize];
    //first element
    result[0] = data[0];
    int i, j, count;
    
    printf("\n");
    //insersion sort
    for(i = 1; i < dataSize; i++) {
        count = i - 1;
        
        while(count >= 0 && result[count] > data[i]) {
            count = count - 1;
        }
        
        //moves variables
        for(j = i; j > count; j--) {
            result[j] = result[j - 1];
        }
        
        //final variable
        result[count + 1] = data[i];
    }
    
    int m;
    for(m = 0; m < dataSize; m++) {
        sortedData[m] = result[m];
    }
    printf("\ndid sorting\n");
    fflush(stdout);
    
    pthread_exit(0);
}

//indexes: min = 0, med = 1, max =2
//finds the minimum, median and max of the data
//assumes data is sorted
void minMedMax(double data[]) { //returns array of min, median, and max
    //number of elements in the data set
    int dataSize = (sizeof(data)/sizeof(data[0]));
    
    if(dataSize % 2 == 1) { //data size is odd
        median = data[(dataSize - 1) / 2];
    } else { //data size is even
        double val1 = data[dataSize / 2]; //first middle value
        double val2 = data[(dataSize - 2) / 2]; //second middle value
        median = (val1 + val2) / 2;
    }
    
    min = data[0];
    max = data[dataSize];
    
    pthread_exit(0);
}

//assumes data is sorted
//returns values that make quartiles
//quartile data index: 0 is first quartile, 1 is third quartile
void quartile(double data[]) {
    //Yes, we could have just reuesed the "median" method, but that would have required copying over the array twice, which is eh
    double firstQuartile = 0;
    double thirdQuartile = 0;
    if((sizeof(data)/sizeof(data[0])) % 4 == 0) { //if an even number of things
        firstQuartile = (data[(sizeof(data)/sizeof(data[0])) / 4] + data[(sizeof(data)/sizeof(data[0])) / 4 - 1]) / 2;
        thirdQuartile = (data[((sizeof(data)/sizeof(data[0])) / 4)*3] + data[((sizeof(data)/sizeof(data[0])) / 4)*3 - 1]) / 2;
    } else if ((sizeof(data)/sizeof(data[0])) % 4 == 1) {
        firstQuartile = data[(sizeof(data)/sizeof(data[0])) / 4];
        thirdQuartile = data[((sizeof(data)/sizeof(data[0])) / 4)*3];
    } else if ((sizeof(data)/sizeof(data[0])) % 4 == 2) {
        firstQuartile = data[(sizeof(data)/sizeof(data[0])) / 4];
        thirdQuartile = data[((sizeof(data)/sizeof(data[0])) / 4)*3 + 1];
    } else {
        firstQuartile = (data[(sizeof(data)/sizeof(data[0])) / 4] + data[(sizeof(data)/sizeof(data[0])) / 4 + 1]) / 2;
        thirdQuartile = (data[((sizeof(data)/sizeof(data[0])) / 4)*3 + 1] + data[((sizeof(data)/sizeof(data[0])) / 4)*3 + 2]) / 2;
    }
    
    quartileData[0] = firstQuartile;
    quartileData[1] = thirdQuartile;
    
    pthread_exit(0);
}

//returns the standard deviation of the data
//assumes data is sorted, and mean is found
void sd(double data[]) {
    int dataSize = (sizeof(data)/sizeof(data[0]));
    double myMean = meanVal;
    double sum = 0;
    int i;
    for(i = 0; i < dataSize; i++) {
        sum += (myMean - data[i]) * (myMean - data[i]);
    }
    
    standardDeviation = sqrt(sum / dataSize);
    pthread_exit(0);
}

//returns the mode of the data
//assumes data is sorted
void mode(double data[]){
    //TODO: Make so can account for either multiple modes, or no modes
    int dataSize = (sizeof(data)/sizeof(data[0]));
    double EPSILON = 0.000001; //for purposes of comparing doubles
    
    double currentMode = data[0];
    int maxTimesOccured = 1;
    int i = 0;
    while(i < dataSize && (abs(data[i] - currentMode) < EPSILON)) {
        maxTimesOccured++;
        i++;
    }
    double beingChecked = data[i];
    i++;
    int timesOccured = 1;
    while(i < dataSize) {
        if(abs(data[i] - beingChecked) < EPSILON) { //if found another instance
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
    
    globMode = currentMode;
    pthread_exit(0);
}

// Caitlin Campbell and Shanti Polara Final Project
//Beta version
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
/*INSERT THIS*/
typedef struct myData {
    double *data;
    int size;
};

/*in order for the threads to function, they must be joined all at once, but called 
one by one, they should have seperate variables they modify*/
void mean(struct myData *input);
void sort(struct myData *input);
void minMedMax(struct myData *input); //returns array of min, median, and max
void quartile(struct myData *input); //returns
void sd(struct myData *input);
void mode(struct myData *input);


double quartileData[2];
double meanVal, standardDeviation, min, median, max, globMode;
double *sortedData;




int main(int argc, char *argv[]){
    
    
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
    
    /*
    //sort has to sort the data before any of the methods that require sorted data run
    pthread_create(&tid[0], &attr, sort, &mainData);
    sleep(1);
    
    printf("\ndid\n\n");
    fflush(stdout);*/
    /*
    int i;
    for(i = 0; i < mainData.size; i++) {
        printf("%.2f ", sortedData[i]);
    }
    return 0;*/
}

//returns the mean
void mean(struct myData *input) {
    int numOfData = input->size;
    double sum = 0;
    int i;
    for(i = 0; i < numOfData; i++) {
        sum += input->data[i];
    }
    double myMean = (sum / numOfData);
    
    pthread_exit(&myMean);
}

//returns sorted list of data
void sort(struct myData *input) {
    int dataSize = input->size;
    
    double result[dataSize];
    //first element
    result[0] = input->data[0];
    int i, j, count;
    
    printf("\n");
    //insersion sort
    for(i = 1; i < dataSize; i++) {
        count = i - 1;
        
        while(count >= 0 && result[count] > input->data[i]) {
            count = count - 1;
        }
        
        //moves variables
        for(j = i; j > count; j--) {
            result[j] = result[j - 1];
        }
        
        //final variable
        result[count + 1] = input->data[i];
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
void minMedMax(struct myData *input) { //returns array of min, median, and max
    //number of elements in the data set
    int dataSize = input->size;
    
    if(dataSize % 2 == 1) { //data size is odd
        median = input->data[(dataSize - 1) / 2];
    } else { //data size is even
        double val1 = input->data[dataSize / 2]; //first middle value
        double val2 = input->data[(dataSize - 2) / 2]; //second middle value
        median = (val1 + val2) / 2;
    }
    
    min = input->data[0];
    max = input->data[dataSize];
    
    pthread_exit(0);
}

//assumes data is sorted
//returns values that make quartiles
//quartile data index: 0 is first quartile, 1 is second quartile
void quartile(struct myData *input) {
    //Yes, we could have just reuesed the "median" method, but that would have required copying over the array twice, which is eh
    int i;
    for(i = 0; i < input->size; i++) {
        printf("%.1f ", input->data[i]);
    }
    printf("\n\n");
    
    double firstQuartile = 0;
    double thirdQuartile = 0;
    if(input->size % 4 == 0) { //if an even number of things
        firstQuartile = (input->data[input->size / 4] + input->data[input->size / 4 - 1]) / 2;
        thirdQuartile = (input->data[(input->size / 4)*3] + input->data[(input->size / 4)*3 - 1]) / 2;
    } else if (input->size % 4 == 1) {
        firstQuartile = input->data[input->size / 4];
        thirdQuartile = input->data[(input->size / 4)*3];
    } else if (input->size % 4 == 2) {
        firstQuartile = input->data[input->size / 4];
        thirdQuartile = input->data[(input->size / 4)*3 + 1];
    } else {
        firstQuartile = (input->data[input->size / 4] + input->data[input->size / 4 + 1]) / 2;
        thirdQuartile = (input->data[(input->size / 4)*3 + 1] + input->data[(input->size / 4)*3 + 2]) / 2;
    }
    
    quartileData[0] = firstQuartile;
    quartileData[1] = thirdQuartile;
    
    pthread_exit(0);
}

//returns the standard deviation of the data
//assumes data is sorted, and mean is found
void sd(struct myData *input) {
    int dataSize = input->size;
    double myMean = meanVal;
    double sum = 0;
    int i;
    for(i = 0; i < dataSize; i++) {
        sum += (myMean - input->data[i]) * (myMean - input->data[i]);
    }
    
    standardDeviation = sqrt(sum / dataSize);
    pthread_exit(0);
}

//returns the mode of the data
//assumes data is sorted
void mode(struct myData *input){
    //TODO: Make so can account for either multiple modes, or no modes
    int dataSize = input->size;
    double EPSILON = 0.000001; //for purposes of comparing doubles
    
    double currentMode = input->data[0];
    int maxTimesOccured = 1;
    int i = 0;
    while(i < dataSize && (abs(input->data[i] - currentMode) < EPSILON)) {
        maxTimesOccured++;
        i++;
    }
    double beingChecked = input->data[i];
    i++;
    int timesOccured = 1;
    while(i < dataSize) {
        if(abs(input->data[i] - beingChecked) < EPSILON) { //if found another instance
            timesOccured++;
        } else {
            if(timesOccured > maxTimesOccured) {
                maxTimesOccured = timesOccured;
                currentMode = beingChecked;
            }
            
            beingChecked = input->data[i];
            timesOccured = 1;
        }
        i++;
    }
    
    globMode = currentMode;
    pthread_exit(0);
}

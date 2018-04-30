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
void mean(struct myData *input);
void sort(struct myData *input);
void minMedMax(struct myData *input); //returns array of min, median, and max
void quartile(struct myData *input); //returns
void sd(struct myData *input);
void mode(struct myData *input);

double quartileData[2];
double meanVal, standardDeviation, min, median, max, globMode;
double sortedData[];

int main(int argc, char *argv[]){
    printf("sorted stuff");
    int threadcount = 0; //keeps track of how many threads are being used
    pthread_attr_t attr; // set of attributes for the thread
    pthread_attr_init(&attr); // get the default attributes
    
    median = 2;
    
    double data[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}; //input data
    //initialize thread ids
    pthread_t tid[6];
    
    /*MAKE STRUCT*/
    struct myData mainData;
    mainData.data = data;
    mainData.size = (sizeof(data)/sizeof(data[0]));
    
    sortedData[mainData.size];
    printf("will sort stuff\n");
    pthread_create(&tid[0], &attr, sort, &mainData);
    pthread_join(tid[0], NULL);
    printf("sorted stuff\n");
    
    mainData.data = sortedData;
    
    pthread_create(&tid[1], &attr, minMedMax, &mainData);
    pthread_join(tid[1], NULL);
    
    printf("Median: %.2f", median);

    return 0;
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
    meanVal = myMean;
    pthread_exit(&myMean);
}

//returns sorted list of data
void sort(struct myData *input) {
    int dataSize = input->size;
    double result[dataSize];
    
    //first element
    result[0] = input->data[0];
    
    int i, j, count;
    
    //insersion sort
    for(i = 1; i < dataSize; i++) {
        count = i - 1;
        
        //finds proper place
        while(count >= 0 && result[count] > input->data[i]) {
            count--;
        }
        
        //moves variables
        for(j = i; j > count; j--) {
            result[j] = result[j - 1];
        }
        
        //final variable
        result[count + 1] = input->data[i];
        
        int p;
    }
    
    //moves into sortedData
    int m;
    for(m = 0; m < dataSize; m++) {
        sortedData[m] = result[m];
    }
    pthread_exit(0);
}

//indexes: min = 0, med = 1, max =2
//finds the minimum, median and max of the data
//assumes data is sorted
void minMedMax(struct myData *input) { //returns array of min, median, and max
    //number of elements in the data set
    int dataSize = input->size;
    printf("Size: %d\n", dataSize);
    fflush(stdout);
    printf("Min testing: \n");
    int i;
    for(i = 0; i < dataSize; i++) {
        printf("%.2f, ", input->data[i]);
    }
    printf("okay...%.2f, %d\n\n", median, (dataSize % 2));
    if(dataSize % 2 == 1) { //data size is odd
        median = input->data[(dataSize - 1) / 2];
    } else { //data size is even
        printf("okay pt 2...%.2f, %d\n\n", median, (dataSize % 2));
        double val1 = input->data[dataSize / 2]; //first middle value
        double val2 = input->data[(dataSize - 2) / 2]; //second middle value
        printf("okay pt 3 %.2f, %d\n\n", median);
        median = (val1 + val2) / 2;
        printf("okay...%.2f, %d\n\n", median);
    }
    
    min = input->data[0];
    max = input->data[dataSize - 1];
    
    pthread_exit(0);
}

//assumes data is sorted
//returns values that make quartiles
//quartile data index: 0 is first quartile, 1 is third quartile
void quartile(struct myData *input) {
    //Yes, we could have just reuesed the "median" method, but that would have required copying over the array twice, which is eh
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

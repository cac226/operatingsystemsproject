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
double *sortedData;

int main(int argc, char *argv[]){
    
    
    char line[20]; //recives user input
    char *token; //tokenizes input into an array
    int con, i = 0; //counter value
    
    //keeps track of requested operations on the data using 0, 1 as boolean values
    int ops[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    int badinput = 0; //keeps track of if user inputs non-numbers
    
    int threadcount = 0; //keeps track of how many threads are being used
    pthread_attr_t attr; // set of attributes for the thread
    pthread_attr_init(&attr); // get the default attributes
    FILE *file; //pointer to file to read in values
    FILE *file1; //pointer to file to find num of values to read in
    //checks if correct size of input has been entered
    if (argc == 0 || argc > 1){
        printf("Error: wrong number of arguments\n"
               "please enter the name of the text file containing the data\n");
    }
    
    if ((file = fopen(argv[1], "r"))==NULL) {
        printf("Cannot open file \n");
        exit(1);
    }
    
    file1 = fopen(argv[1], "r"); //reading in file to find size
    char str1[10];
    int count = 0;
    while (fscanf(file1, "%s", str1) == 1){
        if(isdigit(*str1)){
            count++;
        }
    }
    double data[count]; //input data
    sortedData[count]; //alocating size of sortedData to be size of input data
    
    
    //initialize thread ids
    pthread_t tid[6];
    
    /*MAKE STRUCT*/
    struct myData mainData;
    mainData.data = data;
    mainData.size = sizeof(data)/sizeof(data[0]);
    
    
    
    int j = 0; //keeps count of number of threads
    //thread creation for mean, keeping track of number of threads
    if (ops[1] || ops[4]){ //mean
        pthread_create(&tid[5], &attr, mean, &mainData);
        pthread_join(tid[5], NULL);
    }
    
    //checks if user requested median, max or min as operations
    if ((ops[2] || ops[5]) || ops[6]){ //median, max, min
        
        if (ops[2])//median
            printf("median\n");
        if (ops[6]) //minumum
            printf("minimum\n");
        if (ops[5])//maximum
            printf("maximum\n");
        pthread_create(&tid[j], &attr, minMedMax, &mainData);
        threadcount++;
        j++;
    }
    
    //checks if user requested mode as an operation
    if (ops[3]){
        printf("mode\n");
        pthread_create(&tid[j], &attr, mode, &mainData);
        threadcount++;
        j++;
    }
    
    //checks if user requested standard deviation as an operation
    if (ops[4]){
        printf("standard dev\n");
        pthread_create(&tid[j], &attr, sd, &mainData);
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
        pthread_create(&tid[j], &attr, quartile, &mainData);
        threadcount++;
        j++;
    }
    
    for (i = 0; i < threadcount; i++)
        pthread_join(tid[i], NULL);
    
    //print statements for results
    if(ops[1])
        printf("Mean = %.2f\n", meanVal);
    if(ops[2])
        printf("Median = %.2f\n", median);
    if(ops[3])
        printf("Mode = %.2f\n", globMode);
    if(ops[4])
        printf("Standard Deviation = %.2f\n", standardDeviation);
    if(ops[5])
        printf("Maximum Value = %.2f\n", max);
    if(ops[6])
        printf("Minimum Value = %.2f\n", min);
    if(ops[8])
        printf("First Quartile = %.2f\n", quartileData[0]);
    if(ops[9])
        printf("Third Quartile = %.2f\n", quartileData[1]);
    
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
    printf("Mean thing says: %.2f\n", myMean);
    meanVal = myMean;
    pthread_exit(&myMean);
}

//returns sorted list of data
void sort(struct myData *input) {
    printf("working...\n");
    int dataSize = input->size;
    double result[dataSize];
    //first element
    result[0] = input->data[0];
    int i, j, count;
    
    printf("\n");
    //insersion sort
    for(i = 1; i < dataSize; i++) {
        printf("working...\n");
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
    printf("\n\nworking...\n");
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
void minMedMax(struct myData *input) { //returns array of min, median, and max
    printf("working...\n");
    //number of elements in the data set
    int dataSize = input->size;
    printf("working...\n");
    printf("");
    if(dataSize % 2 == 1) { //data size is odd
        printf("working...\n");
        median = input->data[(dataSize - 1) / 2];
    } else { //data size is even
        printf("working...\n");
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

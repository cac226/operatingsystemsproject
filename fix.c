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


void sort(struct myData *input);

double *sortedData;

int main(int argc, char *argv[]){

	
	pthread_attr_t attr; // set of attributes for the thread 
	pthread_attr_init(&attr); // get the default attributes 
	
	double data[4] = {4, 5, 2, 1};
    /*MAKE STRUCT*/
    struct myData mainData;
    mainData.data = data;
    mainData.size = sizeof(data)/sizeof(data[0]);
    
	
	pthread_create(&tid[6], &attr, sort, &mainData);
	pthread_join(tid[6], NULL);
        
    for (i = 0; i < sizeof(mainData.data)/sizeof(mainData.data[0]); i++){
        mainData.data[i] = sortedData[i];
		printf("d: %.2f", mainData.data[i]);
	}

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

=
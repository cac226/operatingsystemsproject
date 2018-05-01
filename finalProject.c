// Caitlin Campbell and Shanti Polara Final Project
// Final Version
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
    int *data;
    int size;
};

/*in order for the threads to function, they must be joined all at once, but called
 one by one, they should have seperate variables they modify*/
void mean(struct myData *input);
void sort(struct myData *input);
void minMedMax(struct myData *input); //returns array of min, median, and max
void quartile(struct myData *input); //returns
void sd(struct myData *input);

double quartileData[2];
double meanVal, standardDeviation, median; //median, mean, and standardDeviantion may be doubles
int sortedData[];
int min, max; //min and max are ints because they will always be a data value

int main(int argc, char *argv[]){

	
	char line[20]; //recives user input
	char *token; //tokenizes input into an array
	int con, i = 0; //counter value
	
	//keeps track of requested operations on the data using 0, 1 as boolean values
	int ops[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	int badinput = 0; //keeps track of if user inputs non-numbers
	
	int threadcount = 0; //keeps track of how many threads are being used
	pthread_attr_t attr; // set of attributes for the thread 
	pthread_attr_init(&attr); // get the default attributes 
	FILE *file; //pointer to file to read in values
	FILE *file1; //pointer to file to find num of values to read in
    
	//checks if valid file
	if ((file = fopen(argv[1], "r"))==NULL) {
		printf("Cannot open file. Please enter a valid file name. \n");
		exit(1);
    }
	 
	file1 = fopen(argv[1], "r"); //reading in file to find size
	char str1[10];
	int count = 0;
	
	//finds size of file
	while (fscanf(file1, "%s", str1) == 1){
		if(isdigit(*str1)){
			count++;
		}
	}
	int data[count]; //input data
    
	char str[10];
	
	//reads in data from file, checks if any values are non-numeric
	while (fscanf(file, "%s", str) == 1){
		if(isdigit(*str)){
			con = atoi(str);
			data[i] = con;
			i++;
		}
		else
			badinput = 1;
	}
	//double sort[(input->size)], minMedmax[3], quartile[2];
	printf("\n\nChoose one or more of the following operations on the data by\n"
			"typing the corresponding number(s) separated by a space\n\n"
			"0)all options \n1)Mean \n2)Median \n3)Standard Deviation \n4)Maximum Value"
			"\n5)Minimum Value \n6)Sorted List \n7)First Quartile \n8)Third Quartile\n\nInput: ");
	fgets(line, 20, stdin);
	token = strtok(line, " ");
    
	//reading in string, making sure only numbers were entered
	while(token != NULL ) {
		if (isdigit(*token)){
			con = *token - '0';
			fflush(stdout);
			if (con <= 8 && con >= 0)
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
    
    /*MAKE STRUCT*/
    struct myData mainData;
    mainData.data = data;
    mainData.size = (sizeof(data)/sizeof(data[0]));
    
    sortedData[mainData.size];
    
	//if user requests all operations, set all operations to true
	if (ops[0]){
		for (i = 1; i < sizeof(ops)/sizeof(ops[0]); i++)
			ops[i] = 1;
	}
	
    
    
	//checks if user is requesting any operations that use a sorted list
	if (ops[2] || ops[4] || ops[5] || ops[6] || ops[7] || ops[8]){
		//sort has to sort the data before any of the methods that require sorted data run
		pthread_create(&tid[6], &attr, sort, &mainData);
		pthread_join(tid[6], NULL);
        mainData.data = sortedData;
	}
	
	
	int j = 0; //keeps count of number of threads
	//thread creation for mean, keeping track of number of threads
	if (ops[1] || ops[3]){ //mean
		pthread_create(&tid[5], &attr, mean, &mainData);
		pthread_join(tid[5], NULL);
	}
	 
	//checks if user requested median, max or min as operations
	if ((ops[2] || ops[4]) || ops[5]){ //median, max, min
		pthread_create(&tid[j], &attr, minMedMax, &mainData);
		threadcount++;	
		j++;
	}
	
	//checks if user requested standard deviation as an operation
	if (ops[3]){
		pthread_create(&tid[j], &attr, sd, &mainData);
		threadcount++;	
		j++;
	}
	

	//checks if user requested first quartile or second quartiles as operations
	if (ops[8] || ops[7]){
		pthread_create(&tid[j], &attr, quartile, &mainData);
		threadcount++;
		j++;
	}
	
    //rejoins all threads
	for (i = 0; i < threadcount; i++)
		pthread_join(tid[i], NULL);
	
    printf("\n\n"); //formatting
    
	//print statements for results
	if(ops[1])
		printf("Mean = %.2f\n", meanVal);
	if(ops[2])
		printf("Median = %.2f\n", median);
    if(ops[3])
        printf("Standard Deviation = %.2f\n", standardDeviation);
	if(ops[4])
		printf("Maximum Value = %d\n", max);
	if(ops[5])
		printf("Minimum Value = %d\n", min);
	if(ops[7])
		printf("First Quartile = %.2f\n", quartileData[0]);
	if(ops[8])
		printf("Third Quartile = %.2f\n", quartileData[1]);
    if(ops[6]) {
		printf("Sorted Data:\n");
		for (i = 0; i < mainData.size; i++){
            printf("%d\t", mainData.data[i]);
            if(i % 10 == 9) {
                printf("\n");
            }
        }
    }
    printf("\n\n"); //formatting
    
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
    int result[dataSize];
    
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
    
    if(dataSize % 2 == 1) { //data size is odd
        median = input->data[(dataSize - 1) / 2];
    } else { //data size is even
        double val1 = input->data[dataSize / 2]; //first middle value
        double val2 = input->data[(dataSize - 2) / 2]; //second middle value
        median = (val1 + val2) / 2;
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

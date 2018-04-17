// Caitlin Campbell and Shanti Polara Final Project
//Beta version
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

double mean(double[] data);
double[] sort(double[] data);
double[] minMedMax(double[] data); //returns array of min, median, and max
double quartile(double[] data); //returns
double sd(double[] data);

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

double mean(double[] data) {
    return 0;
}

double[] sort(double[] data) {
    return data;
}

double[] minMedMax(double[] data) { //returns array of min, median, and max
    return data;
}

double quartile(double[] data) {
    return 0;
}

double sd(double[] data) {
    return 0;
}


#include <stdio.h> // For printf
#include <stdlib.h> // For exit
#include <pthread.h> // For threads
#include <semaphore.h> // For semaphores
#include <math.h>
#include <sys/types.h>

double min;
double child(); /* child thread */

int main(int argc, char *argv[]) {
	// Set up semaphore
	// Prepare the child thread
	min = 0;
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, child, NULL);
	pthread_join(tid, NULL);
	printf("Minima = %.2f\n", min);
}

double child() {
	min = 3;
	return 0;
}

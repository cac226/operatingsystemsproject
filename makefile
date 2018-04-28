all:
	gcc -o finalProject finalProject.c -pthread -lrt -lm -w
	gcc -o testingMethods testingMethods.c -pthread -lrt -lm -w
#include "queue.h"
#include <stdlib.h>
#include <math.h>

#define AVG_SERVICE 2.0

void simulation(int);
double expdist(double);
void readIn(int[], int[], char[]);
int custPerMin(int, int[], int[]);

int main(){
	int i = 0, lastNum = 0 , numOfTellers = 4, customersAdded = 0;
	int customersPerMin[5], customersPercent[5], range[6];	
	time_t t;

	//Intializes random number generator
	srand((unsigned) time(&t));

	readIn(customersPerMin, customersPercent, "/home/olearyt/Documents/CIS/361/proj2/proj2.dat");
	
	//Initialize range to the lowest percent of each section
	range[6] = 100;
	for (i = 4; i > -1; i--){
		if(i == 4){
			range[i] = 100 - customersPercent[i];
			lastNum = range[i];	
		}
		else{
			range[i] = lastNum - customersPercent[i];
			lastNum = range[i];
		}
		//printf("Range at %d: %d\n", i, range[i]);
	}	

	customersAdded = custPerMin(rand() % 100, customersPerMin, range);
	
	/*
	simulation(numOfTellers);
	numOfTellers++;
	simulation(numOfTellers);
        numOfTellers++;
	simulation(numOfTellers);
        numOfTellers++;
	simulation(numOfTellers);
	*/
	exit(0);
	return 0;
}

void simulation(int numOfTellers){
	
}

double expdist(double mean){
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

void readIn(int input[], int input2[], char fname[]){
	FILE *file;

	int i = 0, count1 = 0, count2 = 0;
	int data[10];

	//Open the file and make sure it worked properly
	file = fopen(fname, "r");

	if ( file == NULL){
                printf("Error reading file\n");
                exit (0);
        }

	//scan the file data into given
	for (i = 0; i < 10; i++)
        {
                fscanf(file, " %d", &data[i]);
		//printf("Input %d: %d\n", i, data[i]);
        }

	//split the data into the 2 input arrays
	for(i = 0; i < 10; i++){
		//if even
		if( i % 2 == 0){
			input[count1] = data[i];
			//printf("Customer count: %d\n", input[count1]);
			count1++;
		}
		else {
			input2[count2] = data[i];
			//printf("Percent chance: %d\n", input2[count2]);
			count2++;
		}
	}

	//close the file
	fclose(file);
}

int custPerMin(int percent, int customersMin[], int range[]){
	int i = 0;

	for(i = 0; i < 5; i++){
		if( i <= range[i+1]){
			return customersMin[i];
		}
	}
}

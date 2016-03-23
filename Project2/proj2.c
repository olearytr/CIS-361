#include "queue.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define AVG_SERVICE 2.0

void simulation(int);
double expdist(double);
void readIn(int[], int[], char[]);
int custPerMin(int, int[], int[]);

int main(){
	int numOfTellers = 4;	
	
	simulation(numOfTellers);
	numOfTellers++;
	/*
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
	int i = 0, m = 0, lastNum = 0, customersAdded = 0, percent = 0;
        int customersPerMin[5], customersPercent[5], range[6], tellers[numOfTellers];
        time_t t;
	struct queue waitLine;
	sequenceNum sequenceID = 1;

	//Initialize the queue
	initialize(&waitLine);

	//Intializes random number generator
	srand((unsigned) time(&t));

	//read in the dat file
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

	//Initialize the tellers array, 0 for free, positive for time remaining with customer
	for (i = 0; i < numOfTellers; i++){
		tellers[i] = 0;
	}
	
	//loop through 480 minutes for a work day
	for( i = 0; i < 480; i++){

		//subtract 1 min from each tellers counter
		for(m = 0; m < numOfTellers; m++){
			//only subtract if the counter is greater than 0
			if(tellers[m] > 0){
				tellers[m]--;
			}
		}

		//get a random percent and add the corresponding amount of customers
		percent = rand() % 100;
		printf("Percent: %d\n", percent);
        	customersAdded = custPerMin(percent, customersPerMin, range);
		printf("Corresponding Customers: %d\n", customersAdded);
	
		//add that amount of customers to the queue
		for ( m = 0; m < customersAdded; m++){
			enqueue(sequenceID, &waitLine);
			sequenceID++;
		}

		//any available tellers should service customer next in line
		for ( m = 0; m < numOfTellers; m++){
			if(tellers[m] == 0 && !empty(&waitLine)){
				//dequeue the line, set the tellers count to the random
				//time to service from expdist()
				dequeue(&waitLine);
				tellers[m] = (int)expdist(AVG_SERVICE);
			}
		}

	}

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
		if( percent <= range[i+1]){
			return customersMin[i];
		}
	}

	return -1;
}

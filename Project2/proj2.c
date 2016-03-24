#include "queue.h"
#include "stats.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define AVG_SERVICE 2.0
#define MAX_LINE 1920 /*max amount of customers * 480*/

//T. Ryan O'Leary
//CIS 361 Project 2

void simulation(int);
double expdist(double);
void readIn(int[], int[], char[]);
int custPerMin(int, int[], int[]);

int main(){

	//The number of tellers
	int numOfTellers = 4;	
	
	//Run the simulation 4 times, increasing the amount of tellers each time
	simulation(numOfTellers);
	numOfTellers++;
	printf("\n");
	simulation(numOfTellers);
        numOfTellers++;
	printf("\n");
	simulation(numOfTellers);
        numOfTellers++;
	printf("\n");
	simulation(numOfTellers);
	
	exit(0);
	return 0;
}

 /*
 * Simulates the average 8 hour work day
 * @param numOfTellers - The number of tellers available
 */
void simulation(int numOfTellers){

	/* Vars for loops, remembering the last num, how many customers are added
 	*  each minute, and the percent that corresponds to it. */ 	
	int i = 0, m = 0, lastNum = 0, customersAdded = 0, percent = 0;

	/* Arrays that hold up to 5 values for input from the dat file, the range 
 	*  that corresponds to the input percents, and an array to represent each teller */	
        int customersPerMin[5], customersPercent[5], range[6], tellers[numOfTellers];

	/* start, end, and length arrays for stats */
        int start[MAX_LINE], end[MAX_LINE], length[MAX_LINE];

	/* Time for the rand() generator */
	time_t t;

	/* The queue */
	struct queue waitLine;

	/* the sequence ID for each customers, ending ID */
	sequenceNum sequenceID = 1, endID = 0;

	//Initialize the queue
	initialize(&waitLine);

	//Intializes random number generator
	srand((unsigned) time(&t));

	//read in the dat file
        readIn(customersPerMin, customersPercent, "/home/olearyt/Documents/CIS/361/proj2/proj2.dat");

	//Initialize range to the lowest percent of each section
	range[5] = 100;
        for (i = 4; i > -1; i--){
                if(i == 4){
                        range[i] = 100 - customersPercent[i];
                        lastNum = range[i];
                }
                else{
                        range[i] = lastNum - customersPercent[i];
                        lastNum = range[i];
                }
	}

	 //Tests for correct values of range
	/*for (i = 0; i < 6; i++){
		printf("Range at %d: %d\n", i, range[i]);
	}*/

	//Initialize the tellers array, 0 for free, positive for time remaining with customer
	for (i = 0; i < numOfTellers; i++){
		tellers[i] = 0;
	}

	//Initialize start, end, and length arrays to 0
	for (i = 0; i < MAX_LINE; i++){
		start[i] = 0;
		end[i] = 0;
	}

	for ( i = 0; i < 480; i++){
		length[i] = 0;
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
		//printf("Percent: %d\n", percent);
        	customersAdded = custPerMin(percent, customersPerMin, range);
		//printf("Corresponding Customers: %d\n", customersAdded);
	
		//add that amount of customers to the queue and add each customer's start time to start
		for ( m = 0; m < customersAdded; m++){
			enqueue(sequenceID, i, &waitLine);
			start[sequenceID] = i;
			//printf("Start time for customer %d: %d\n", sequenceID, start[sequenceID]);
			sequenceID++;
		}

		//update the length of the line every minute
		length[i] = size(&waitLine); 

		//any available tellers should service customer next in line
		for ( m = 0; m < numOfTellers; m++){
			if(tellers[m] == 0 && !empty(&waitLine)){
				//dequeue the line, set the tellers count to the random
				//time to service from expdist(). Add the end time to end
				endID = dequeue(&waitLine);
				end[endID] = i;
				//printf("End time for customer %d: %d\n", endID, end[endID]); 
				tellers[m] = (int)expdist(AVG_SERVICE);
			}
		}

	}

	//Print the stats
	printf("Tellers: %d\n", numOfTellers);	
	printf("Total served: %d\n", totalServed(sequenceID-1));
	printf("Total not served due to the end of the work day: %d\n", notServed(start, end, MAX_LINE));
	printf("Average time spent waiting: %d\n", avgWait(start, end, MAX_LINE));
	printf("Max time spent waiting: %d\n", maxWait(start, end, MAX_LINE));
	printf("Average length of line: %d\n", avgLength(length, 480));
	printf("Max length of line: %d\n", maxLength(length, 480));

}

 /*
 * Returns a unique time for a teller to service a customer based on the mean
 */
double expdist(double mean){
	double r = rand();
	r /= RAND_MAX;
	return -mean * log(r);
}

 /*
 * Reads in the input file fname and stores each col of data in arrays
 * input and input2.
 * @param input - Array for the first col of data
 * @param input2 - Array for 2nd col of data
 * @param fname - the file to be used as input
 */ 
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

 /* 
 * Returns the amount of customers added based on the percent
 * @param percent - the random percent
 * @param customersMin - Array holding the amount of customers to add
 * @param range - array holding the range
 */
int custPerMin(int percent, int customersMin[], int range[]){
	int i = 0;

	//if the percent is less than or equal to a range value,
	//use the corresponding value for customers to add
	for(i = 0; i < 5; i++){
		if( percent <= range[i+1]){
			return customersMin[i];
		}
	}
	
	//if none found, return error
	return -1;
}

#include "stats.h"

 /*
 * Returns the total amount served
 */
int totalServed(int served){
	return served;
}

 /*
 * Calculates the average waiting time
 * @param start - the start time for each potential customer
 * @param end - the end time for each potential cutomer
 * @param size - the size of the arrays
 */
int avgWait(int start[], int end[], int size){
	int total = 0, i = 0, actual = 0;;
	int avgs[size];

	//Run through every spot of the arrays
	for( i = 0; i < size; i++){
	
		// if they are both 0, then no customer ever filled that spot,
		// so skip it (set to -1)
		if(end[i] == 0 && start[i] == 0){
			avgs[i] = -1;
		}

		// if end is 0 and start is not, then a customer filled that
		// spot but was not served, skip it
		if (end[i] == 0 && start[i] > 0){
			avgs[i] = -1;
		}

		// otherwise set the wait time (end time - start time),
		// and increment the actual amount of customers
		else {
		   avgs[i] = end[i] - start[i];
		   actual++;
		}	
	}

	//add all the values of the array, if the spot is -1, skip it
	for( i = 0; i < size; i++){
		if(avgs[i] == -1){
			;
		}
		else{
		   total += avgs[i];
		}
	}

	//return the average
	return total/actual;
}

 /*
 * Returns the max waiting time 
 * @param start - the start time for each potential customer
 * @param end - the end time for each potential cutomer
 * @param size - the size of the arrays
 */
int maxWait(int start[], int end[], int size){
	int i = 0, max = 0;
	int time[size];

	//Find the wait times for all customers
	for( i = 0; i < size; i++){
                time[i] = end[i] - start[i];
        }

	//if a wait time is larger than the previous
	//max, set the max to that
	for ( i = 0; i < size; i++){
		if (time[i] > max){
			max = time[i];
		}
	}

	//return the max wait time
	return max;

}

 /*
 * returns the average length of the line
 * @param lengths - the lengths at every min
 * @param size - the size of the array
 */
int avgLength(int lengths[], int size){
	int i = 0, avgs = 0;

	//add up all of the lengths
	for (i = 0; i  < size; i++){
		avgs += lengths[i];
	}

	//return the average
	return avgs/size;
}

 /*
 * returns the max length of the line
 * @param lengths - the lengths at every min
 * param size - the size of the array
 */
int maxLength(int lengths[], int size){
	int i = 0, max = 0;

	//if there is a larger max, set max to that value
	for (i = 0; i < size; i++){
		if(lengths[i] > max){
			max = lengths[i];
		}
	}
	
	//return the max
	return max;
}

 /*
 * Returns the amount of customers not served
 * @param start - the start time for all potential customers
 * @param end - the end time for all potential customers
 * @param size - the size of the arrays
 */
int notServed(int start[], int end[], int size){
	int i = 0, counter = 0;

	//Increase the counter if the start time is not 0 
	//but the end time is 0
	for ( i = 0; i < size; i++){
		if(start[i] > 0 && end[i] == 0){
			counter++;
		}
	}
	
	//return the counter
	return counter;
}

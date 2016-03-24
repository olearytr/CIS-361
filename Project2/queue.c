#include "queue.h"

//Initializes the queue
void initialize(queue *q){
	q -> count = 0;
	q -> front = NULL;
	q -> end = NULL;
}

//Queue the next customer to the end of the line
void enqueue(sequenceNum n, int arrival, queue *q){
	customer *c;

	c = malloc(sizeof(customer));
	c -> num = n;
	c -> arrivalTime = arrival;
	c -> next = NULL;
	if (!empty(q)){
		q -> end -> next = c;
		q-> end = c;
	}
	else {
		q -> front = q -> end = c;
	}
	
	q -> count++;
}

//Dequeue the person at the front of the line
sequenceNum dequeue(queue *q){
	sequenceNum n;
	customer *c;
	
	n = q -> front -> num;
	c = q -> front; 
	q -> front = q -> front -> next;
	q -> count--;
	free(c);
	return n;
}

//Returns the sequenceNum of the customer in front
sequenceNum front(const queue *q){
	return (q -> front -> num);
}

//Checks if the queue is empty or not
boolean empty(const queue *q){
	return ((boolean)(q -> count == EMPTY));
}

//Checks if the queue is full or not
boolean full(const queue *q){
	return ((boolean)(q -> count == FULL));
}

//Returns the size of the queue
int size(queue *q){
	return q -> count;
}

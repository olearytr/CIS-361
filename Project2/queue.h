#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 1920 //Max number of customers * 480 mins in a workday (4 * 480)

typedef int sequenceNum;
typedef enum{false,true} boolean;

//Every customer will have a sequence ID, arrival time, 
//and spot for a customer behind them
struct customer {
	sequenceNum num;
	int arrivalTime;
	//int serviceTime;
	struct customer *next;
};

typedef struct customer customer;

//Every queue will have a count for how many customers
//there are in it, a front spot, and an end spot
struct queue {
	int count;
	customer *front;
	customer *end;
};

typedef struct queue queue;

void initialize(queue *q);
void enqueue(sequenceNum n, int arrival, queue *q);
sequenceNum dequeue(queue *q);
sequenceNum front(const queue *q);
boolean empty(const queue *q);
boolean full(const queue *q);
int size(queue *q);

#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define EMPTY 0
#define FULL 1920

typedef int sequenceNum;
typedef enum{false,true} boolean;

struct customer {
	sequenceNum num;
	int arrivalTime;
	struct customer *next;
};

typedef struct customer customer;

struct queue {
	int count;
	customer *front;
	customer *end;
};

typedef struct queue queue;

void initialize(queue *q);
void enqueue(sequenceNum n, queue *q);
sequenceNum dequeue(queue *q);
sequenceNum front(const queue *q);
boolean empty(const queue *q);
boolean full(const queue *q);

#include "queue.h"

void initialize(queue *q){
	q -> count = 0;
	q -> front = NULL;
	q -> end = NULL;
}

void enqueue(sequenceNum n, queue *q){
	customer *c;

	c = malloc(sizeof(customer));
	c -> num = n;
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

sequenceNum front(const queue *q){
	return (q -> front -> num);
}

boolean empty(const queue *q){
	return ((boolean)(q -> count == EMPTY));
}

boolean full(const queue *q){
	return ((boolean)(q -> count == FULL));
}

int main(){
	return 0;
}

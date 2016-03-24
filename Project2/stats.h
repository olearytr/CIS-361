#ifndef STATS_HEADER
#define STATS_HEADER

int totalServed(int served);
int avgWait(int start[], int end[], int size);
int maxWait(int start[], int end[], int size);
int avgLength(int lengths[], int size);
int maxLength(int lengths[], int size);
int notServed(int start[], int end[], int size);

#endif

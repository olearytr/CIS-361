proj2: proj2.o queue.o stats.o
	gcc -Wall -lm proj2.o queue.o stats.o -o proj2
proj2.o: proj2.c queue.h stats.h
	gcc -c proj2.c
queue.o: queue.c queue.h
	gcc -c queue.c
stats.o: stats.c stats.h
	gcc -c stats.c

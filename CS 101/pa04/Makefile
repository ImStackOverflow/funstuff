PA = pa04-incomplete
CFLAGS = -g -Wall -O0 -std=c99 -D_SVID_SOURCE
CC = gcc
INPUT = -p 2 test1.in

greedy04: greedy04.o
	$(CC) -o greedy04 $(FLAGS) greedy04.o adjWgtVec.o loadGraph.o utilities.o minPQ.o logic.o

greedy04.o: greedy04.c adjWgtVec.c loadGraph.c utilities.c minPQ.c logic.c
	$(CC) -c $(FLAGS) greedy04.c adjWgtVec.c loadGraph.c utilities.c minPQ.c logic.c

clean:
	rm greedy04 greedy04.o adjWgtVec.o loadGraph.o utilities.o minPQ.o logic.o

check:
	valgrind --leak-check=yes greedy04 $(INPUT)

debug:
	gcc -g greedy04.c adjWgtVec.c loadGraph.c utilities.c minPQ.c logic.c -o  greedy04
	gdb greedy04
git:
	git add -A
	git commit -m "fuck me fucke me fuck me"
	git pull
	git push

submit:
	submit cmps101-avg.s17 $(PA) greedy04.c adjWgtVec.c loadGraph.c utilities.c minPQ.c logic.c README.txt Makefile test1.in test2.in test3.in test4.in adjWgtVec.h loadGraph.h utilities.h minPQ.h logic.h 

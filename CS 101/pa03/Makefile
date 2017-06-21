PA = pa03-incomplete
FLAGS = -std=c99 -g
CC = gcc

scc03: scc03.o
	$(CC) -o scc03 $(FLAGS) scc03.o intVec.o loadGraph.o dfstrace1.o

scc03.o: scc03.c intVec.c loadGraph.c dfstrace1.c
	$(CC) -c $(FLAGS) scc03.c intVec.c loadGraph.c dfstrace1.c

clean:
	rm scc03 scc03.o intVec.o loadGraph.o dfstrace1.o

check:
	valgrind --leak-check=yes scc03 test2.in

debug:
	gcc -g scc03.c intVec.c loadGraph.c dfstrace1.c -o  scc03
	gdb scc03
git:
	git add -A
	git commit -m "fuck me fucke me fuck me"
	git pull
	git push

submit:
	submit cmps101-avg.s17 $(PA) scc03.c intVec.c loadGraph.c dfstrace1.c loadGraph.h intVec.h dfstrace1.h test1.in test2.in test3.in test4.in README.txt Makefile

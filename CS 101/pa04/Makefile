PA = pa04
TARGET = greedy04
SRCS = greedy04.c adjWgtVec.c loadGraph.c utilities.c minPQ.c logic.c
FLAGS = -std=c99
DEBUG = -g
OBJS = ${SRC:.c = .o}
HEADER = adjWgtVec.h loadGraph.h utilities.h minPQ.h logic.h
INPUT = -p 2 test1.in
INPUTS = test1.in test2.in test3.in test5.in	

$(TARGET): $(SRCS)
	gcc $(FLAGS) -o $(TARGET) $(SRCS)

clean:
	rm $(TARGET) $(OBJS)

check:
	valgrind --leak-check=yes $(TARGET) $(INPUT)

debug:
	gcc $(DEBUG) $(SRCS) -o  $(TARGET)
	gdb $(TARGET)
git:
	git add -A
	git commit -m "fuck me fucke me fuck me"
	git pull
	git push

submit:
	submit cmps101-avg.s17 $(PA) $(SRCS) $(HEADER) $(INPUTS) README.txt Makefile

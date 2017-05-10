PA = pa02
TARGET = graph02
SRCS = graph02.c intVec.c loadGraph.c
FLAGS = -std=c99 -o
DEBUG = -g
OBJS = ${SRC:.c = .o}
HEADER = loadGraph.h intVec.h  
INPUT = test4.in
INPUTS = test1.in test2.in test3.in test5.in	

$(TARGET): $(SRCS)
	gcc $(FLAGS) $(TARGET) $(SRCS)

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

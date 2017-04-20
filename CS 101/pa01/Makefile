TARGET = graph01
SRCS = graph01.c intVec.c
FLAGS = -std=c99 -o
OBJS = ${SRC:.c = .o}
INPUT = test4.in	

$(TARGET): $(SRCS)
	gcc $(FLAGS) $(TARGET) $(SRCS)

clean:
	rm $(TARGET) $(OBJS)

check:
	valgrind --leak-check=yes $(TARGET) $(INPUT)

TARGET = graph01
SRCS = graph01.c intVec.c
FLAGS = -std=c99 -o
OBJS = ${SRC:.c = .o}
INPUT =	

$(TARGET): $(SRCS)
	gcc $(FLAGS) $(TARGET) $(SRCS)

clean:
	rm $(TARGET) $(OBJS)

check:
	valgrind --leak-check=yes $(TARGET) $(INPUT)

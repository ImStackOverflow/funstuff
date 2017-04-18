charType:charType.c
	gcc -o charType charType.c
	touch output
	./charType charType.c output

clean:
	rm charType output

check:
	valgrind --leak-check=full ./charType charType.c output

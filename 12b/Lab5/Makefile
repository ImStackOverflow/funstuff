CC=gcc
CFLAGS=-I.
DEPS = DictionaryClient.h IntegerLinkedList.h Dictionary.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

DictionaryClient: DictionaryClient.o Dictionary.o IntegerLinkedList.o
	gcc -o DictionaryClient DictionaryClient.c Dictionary.c IntegerLinkedList.c
	touch output
	./DictionaryClient input output

clean:
	rm DictionaryClient.o IntegerLinkedList.o Dictionary.o DictionaryClient output
check:
	valgrind --leak-check=full ./DictionaryClient penis myvagina


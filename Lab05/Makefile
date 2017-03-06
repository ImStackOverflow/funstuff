CC=gcc
CFLAGS=-I.
DEPS = DictionaryClient.h IntegerLinkedList.h Dictionary.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

DictionaryClient: DictionaryClient.o Dictionary.o IntegerLinkedList.o
	gcc -o DictionaryClient DictionaryClient.c Dictionary.c IntegerLinkedList.c

clean:
	rm DictionaryClient.o Dictionary.o IntegerLinkedList.o DictionaryClient

check:
	valgrind --leak-check=full ./charType charType.c output


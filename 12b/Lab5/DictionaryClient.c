#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "IntegerLinkedList.h"

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("wrong shit dude input the correct files\n");
		exit(0);
		
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");
	
	LinkedList list = newLinkedList();
	char str[16];

	while (fgets(str, 16, in)){
		doShit(str, list, out);
		//puts(str);
	}
	freeLinkedList(&list);
	//printf("str 1 = %c str 2 = %c", str[0], str[1]);
	return 0;
}
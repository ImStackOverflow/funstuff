#include <stdio.h>
#include "IntegerLinkedList.h"

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("wrong shit dude input the correct files\n");
	}
	FILE* in = fopen(argv[1], "r");
	FILE* out = fopen(argv[2], "w");

	char str[16];
	fgets(str, 16, in);
	puts(str);
	printf("str 1 = %c str 2 = %c", str[0], str[1]);
	return 0;
}
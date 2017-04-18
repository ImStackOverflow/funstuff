#include "Dictionary.h"
#include <stdlib.h>
#include <string.h>
#include "IntegerLinkedList.h"

void theEye(int data, LinkedList thisDick, FILE* out){
	insert(data, thisDick);
	fprintf(out,"Inserted %d\n", data);
}

void penis(LinkedList pien, FILE* out){
	printLinkedList(out, pien);
}

void dick(int data, LinkedList d, FILE* out){
	if (find(data, d) != NULL){	
		delete(data, d);
		fprintf(out, "deleted %d\n", data);
	}
	else {
		fprintf(out, "cannot delete %d, not in linked list\n", data);
	}
}

void fiend(int data, LinkedList d, FILE* out){
	if (find(data, d) != NULL){
		fprintf(out, "%d present\n", data);
	}
	else {
		fprintf(out, "%d not in list\n", data);
	}
}

void doShit(const char *ass, LinkedList S, FILE* out){
	//printf("at doShit\n");
	switch (*ass){
		case 'i':
			//printf("going into theeye, data: %d\n", atoi(ass+1));
			theEye(atoi(ass+1), S, out);
			break;
			
		case 'd':
			//printf("going into dick\n");
			dick(atoi(ass+1), S, out);
			break;
		case 'f':
			//printf("going into fiend\n");
			fiend(atoi(ass+1), S, out);
			break;
		case 'p':
		//printf("penis\n");
			penis(S,out);
			break;
	}
}

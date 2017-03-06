#include "Dictionary.h"
#include "IntegerLinkedList.h"

void theEye(int data, LinkedList thisDick, FILE* out){
	insert(data, thisDick);
	fprintf(out,"Inserted %d", data);
}

void penis(LinkedList pien, FILE* out){
	printLinkedList(out, pien);
}

void dick(int data, LinkedList d, FILE* out){
	if (find(data, d) != NULL){	
		delete(data, d);
		fprintf(out, "deleted %d", data);
	}
	else {
		fprintf(out, "cannot delete %d, not in linked list", data);
	}
}

void fiend(int data, LinkedList d, FILE* out){
	if (find(data, d) != NULL){
		fprintf(out, "%d present", data);
	}
	else {
		fprintf(out, "%d not in list", data);
	}
}

void doShit(const char *ass, LinkedList S, FILE* out){
	switch (*ass){
		case 'i':
			theEye(atoi(ass), S, out);
			break;
			
		case 'd':
			dick(atoi(ass), S, out);
			break;
		case 'f':
			fiend(atoi(ass), S, out);
			break;
		case 'p':
			penis(S,out);
			break;
	}
}

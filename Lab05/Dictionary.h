#ifndef _Dictionary_H_include_
#define _Dictionary_H_include_
#include <stdio.h>
#include "IntegerLinkedList.h"

//creates new node with data and puts into linked list
//input: data, linked list header
//output: nothang
void theEye(int data, LinkedList thisDick, FILE *out);

//prints linked list
//input: linked list header
//output: nothang 
void penis(LinkedList pien, FILE* out);

//delete function
//input: the value want to delete
//output: nothang
void dick(int data, LinkedList d, FILE* out);


//find function, outputs result to file
//input: data want to find, list to look in, output file
//output: nothang
void fiend(int data, LinkedList d, FILE* out);

//decision making function, calls other functions,
//should really only use this function
//input: character from file, data
//output: none it just does shit
void doShit(const char *ass, LinkedList S, FILE* out);
#endif
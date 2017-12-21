#include "Tree.h"
#include "BOARD.h"
#include "Morse.h"

Node *TreeCreate(int level, const char *data)
{
    Node *yourMom = (Node *) malloc(sizeof (Node));
    if (yourMom) {
	if (level == 1) {//termination case
	    yourMom->leftChild = yourMom; //link end node to itself
	    yourMom->rightChild = yourMom;
	    yourMom->data = MORSE_CHAR_END_OF_CHAR; //store fault data
	    return yourMom;
	} else {
	    yourMom->data = *data; //set data
	    yourMom->leftChild = TreeCreate(level - 1, data + 1); //pass next data to right child
	    yourMom->rightChild = TreeCreate(level - 1, data + (1 << (level - 1))); //pass next data to left child
	    //left data = current data shifted over 2^level-1 times
	}
	return yourMom;
    } else {
	return STANDARD_ERROR; //if memory not allocated correctly
    }
}
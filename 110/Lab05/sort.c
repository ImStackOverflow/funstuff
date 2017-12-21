// Heap size 1024 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "LinkedList.h"

// **** Set any macros or preprocessor directives here ****
//#define LINKED_LIST_TESTING //comment this out once the LinkedList Library is working

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****
static char *dog = "dog";
static char *pig1 = "pig";
static char *pig2 = "pig";
static char *cow = "cow";
static char *cat = "cat";
static char *turtle = "turtle";
static char *bird = "bird";
static char *crab = "crab";

// **** Declare any function prototypes here ****
int InitializeUnsortedWordList(ListItem **unsortedWordList);
int UnsortedWordCount(ListItem *list, int *wordCount);
int SortedWordCount(ListItem *list, int *wordCount);

int main()
{
    BOARD_Init();
#ifdef LINKED_LIST_TESTING
    char *p1, *p2, *p3;
    // *********begin linked list new test*********
    ListItem *Test = LinkedListNew(cow);
    if (strcmp(Test->data, cow) == 0) {
	printf("LinkedListNew is working\n");
    } else {
	printf("LinkedListNew is not working\n");
    }

    // *********begin linked list create after test*********
    ListItem *Testlist = LinkedListNew(cow);
    ListItem *Testlist2 = LinkedListCreateAfter(Testlist, bird);
    ListItem *Testlist3 = LinkedListCreateAfter(Testlist2, crab);
    if (Testlist->nextItem == Testlist2
	    && Testlist2->nextItem == Testlist3
	    && Testlist2->previousItem == Testlist
	    && Testlist3->previousItem == Testlist2
	    && strcmp(Testlist2->data, bird) == 0) {
	printf("LinkedListCreateAfter is working\n");
    } else {
	printf("LinkedListCreateAfter is not working\n");
    }

    // *********begin linked list size test*********
    if (LinkedListSize(Testlist) == 3) {
	printf("LinkedListSize is working\n");
    } else {
	printf("LinkedListSize is not working\n");
    }

    // *********begin linked list get first test*********
    ListItem *test = LinkedListGetFirst(Testlist);
    if (strcmp(test->data, cow) == 0) {
	printf("LinkedListGetFirst is functional\n");
    } else {
	printf("LinkedListGetFirst is not functional\n");
    }

    // *********begin linked list swap data test*********
    LinkedListSwapData(Testlist, Testlist2);
    if (strcmp(Testlist->data, bird) == 0
	    && strcmp(Testlist2->data, cow) == 0) {
	printf("LinkedListSwap is working\n");
    } else {
	printf("LinkedListSwap is not working\n");
    }
    // *********begin linked list sort test*********
    Testlist2->data = NULL;
    LinkedListSort(Testlist);
    p1 = Testlist->data;
    p3 = Testlist3->data; //cant seem to derefrence pointers correctly for non null
    p2 = Testlist2->data;
    if (p1 == NULL
	    && strcmp(p2, cow) == 0
	    && strcmp(p3, crab) == 0) {
	printf("LinkedListSort is working\n");
    } else {
	printf("LinkedListSort is working\n");
    }

    // *********begin linked list print test*********
    Testlist3->data = crab;
    LinkedListPrint(Testlist);
    printf("if LinkedListPrint is functional it should look like this:\n");
    printf("(bird, cow, crab)\n");

    // *********begin linked list remove test*********
    char *test2 = LinkedListRemove(Testlist3);
    if (strcmp(test2, crab) == 0
	    && Testlist2->nextItem == NULL) {
	printf("LinkedListRemove is working\n");
    } else {
	printf("LinkedListRemove is not working\n");
    }
#endif
#ifndef LINKED_LIST_TESTING
    /**
     * ----------------------- STARTER CODE --------------------------
     * This segment of code obtains an unsorted word list, prints it out,
     * and displays the number of occurrences of each word in the list as
     * described by UnsortedWordCount() below.
     **/
    // Initialize an unsorted word list.
    ListItem *unsortedWordList = NULL;
    if (!InitializeUnsortedWordList(&unsortedWordList) || !unsortedWordList) {
	printf("ERROR: Failed to initialize word list\n");
	while (1);
    }

    // Print the list
    LinkedListPrint(unsortedWordList);

    // Get the word counts for every string in the list
    int g = LinkedListSize(unsortedWordList);
    int wordCount[g];

    // Print the word count results
    unsortedWordList = LinkedListGetFirst(unsortedWordList);
    if (UnsortedWordCount(unsortedWordList, wordCount)) {
	printf("unsorted [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n",
		wordCount[0], wordCount[1], wordCount[2],
		wordCount[3], wordCount[4],wordCount[5],
		wordCount[6], wordCount[7], wordCount[8],
		wordCount[9]);
    } else {
	printf("ERROR\n");
    }
    printf("\n");
    /******************************** Your custom code goes below here ********************************/
    ListItem *sortedWords = unsortedWordList; //initilize new list
    
    if (LinkedListSort(sortedWords)) {// sort words
	sortedWords = LinkedListGetFirst(sortedWords);
	LinkedListPrint(sortedWords);
	
	if (SortedWordCount(sortedWords, wordCount)) { //print results
	    printf("sorted [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d]\n",
		    wordCount[0], wordCount[1], wordCount[2],
		    wordCount[3], wordCount[4], wordCount[5],
		    wordCount[6], wordCount[7], wordCount[8],
		    wordCount[9]);
	} else {
	    printf("ERROR\n");
	}
    } else {
	printf("ERROR\n");
    }
    printf("\n");
#endif

    /******************************** Your custom code goes above here ********************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!

    while (1);
}

#ifndef LINKED_LIST_TESTING

int UnsortedWordCount(ListItem *list, int *wordCount)
{
    // Make sure the head of the list was given.
    if (list->previousItem != NULL) {
	return STANDARD_ERROR;
    }

    char *word1;
    char *word2;
    char *repCheck;
    ListItem *item1 = list;
    ListItem *item2;
    int temp, firstOccurencePos;
    int repetitionFlag = 0;
    int i, j;

    i = 0;
    while (item1 != NULL) {
	// Count first occurrence
	j = 1;
	// Ignore NULL words
	word1 = (char *) item1->data;
	if (word1 == NULL) {
	    wordCount[i++] = 0;
	    item1 = item1->nextItem;
	    continue;
	}

	// Check previous occurrences
	temp = i;
	item2 = item1->previousItem;
	while (item2 != NULL) {
	    --temp;
	    repCheck = (char *) item2->data;
	    if (repCheck != NULL && strcmp(repCheck, word1) == 0) {
		repetitionFlag = 1;
		firstOccurencePos = temp;
	    }
	    item2 = item2->previousItem;
	}

	// Count new occurrences
	if (repetitionFlag == 0) {
	    item2 = LinkedListGetFirst(list);
	    while (item2 != NULL) {
		word2 = (char *) item2->data;
		if (word2 != NULL && item1 != item2 && strcmp(word1, word2) == 0) {
		    ++j;
		}
		item2 = item2->nextItem;
	    }
	    wordCount[i++] = j;
	} else {
	    wordCount[i++] = -wordCount[firstOccurencePos];
	    repetitionFlag = 0;
	}
	item1 = item1->nextItem;
    }
    return SUCCESS;
}

int SortedWordCount(ListItem *list, int *wordcount)
{
    int count, j, repflag = 0, i = 0;
    ListItem *list2;
    if (list->previousItem != NULL) {//make sure at head of list
	list = LinkedListGetFirst(list);
    }
    
    list2 = list->nextItem;
    while (list2->nextItem != NULL) {
	if (list->data == NULL) { //null case
	    wordcount[i++] = 0;

	} else {
	    if (strcmp(list->data, list2->data) == 0) {//check if word is repeated
		repflag = 1;
	    }
	    if (repflag == 0) { //if word not repeated add one to wordcount and move on
		wordcount[i++] = 1;
	    } else if (repflag == 1) {
		count = 1;
		while (strcmp(list->data, list2->data) == 0) {//check how many times word occurs
		    count += 1;
		    list = list->nextItem;
		    list2 = list->nextItem;
		}
		wordcount[i++] = count; //set first ocurrence to positive
		for (j = 0; j < count - 1; j++) {
		    wordcount[i++] = -count; //ser all other occurences to negative
		}
		repflag = 0;
		list2 = list;
		list = list->previousItem;
	    }
	}
	list = list->nextItem;
	list2 = list->nextItem;
    }
    list = LinkedListGetFirst(list);
    if (i != LinkedListSize(list)) {//if all elements are not iterated through
	return STANDARD_ERROR;
    } else {
	return SUCCESS;
    }
}

/**
 * This function initializes a list of ListItems for use when testing the LinkedList implementation
 * and word count algorithms.
 *
 * Usage:
 * ListItem *newList;
 * InitializeUnsortedWordList(&newList);
 *
 * @param unsortedWordList[out] Where to store the pointer to the head of the list.
 * @return SUCCESS if it succeeds, STANDARD_ERROR if it fails to allocate necessary memory.
 */
int InitializeUnsortedWordList(ListItem **unsortedWordList)
{
    ListItem *tmp = LinkedListNew(crab);
    if (!tmp) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, pig1)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, cow)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, NULL)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, dog)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, cow)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, bird)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, pig2)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, cat)) {
        return STANDARD_ERROR;
    }
    if (!LinkedListCreateAfter(tmp, turtle)) {
        return STANDARD_ERROR;
    }
    *unsortedWordList = tmp;
    return SUCCESS;
}

/**
 * SortedWordCount() takes in the head of a sorted list of words arranged lexicographically, and an
 * array to store the number of occurrences of each word.  The first time a word appears, the number
 * of occurrences of that word should be stored in the corresponding position in the array.  For
 * duplicate words a negative value of the number of occurrences should be stored.  For example, a
 * list of the following words should return an array with the following values:
 *     {"brush", "brush", "comb", "hair"} -> {2, -2, 1, 1}
 *
 * NULL values are treated as non-strings, so they always count as 0. Every other string is treated
 * as regular strings that can have multiple occurrences, including the empty string, as the
 * following output demonstrates.
 *     {NULL, "platypus", "giraffe", "", "corvid", "slug", "", NULL, "platypus", "platypus"} ->
 *     [0   , 3         , 1        , 2 , 1       , 1     , -2, 0   , -3        , -3}
 *
 * NOTE: This function assumes that wordCount is the same length as list.
 * @param list A pointer to the head of a doubly-linked list containing sorted words.
 * @param wordCount An array of integers. The output of this function is stored here. It must be
 *                  at least as big as the linked list pointed to be `list` is.
 * @return Either SUCCESS or STANDARD_ERROR if the head of the doubly-linked list isn't passed.
 */

#endif

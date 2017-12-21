// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Stack.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries


// **** Set macros and preprocessor directives ****

// **** Define global, module-level, or external variables here ****

// **** Declare function prototypes ****
/*
 * Function prototype for ProcessBackspaces() - This function should be defined
 * below main after the related comment.
 */
int ProcessBackspaces(char *rpn_sentence);

// If this code is used for testing, rename main to something we can call from our testing code. We
// also skip all processor configuration and initialization code.
#ifndef LAB4_TESTING

int main(void)
{
    BOARD_Init();
#else

int their_main(void)
{
#endif // LAB4_TESTING

    /******************************** Your custom code goes below here *******************************/
    printf("Welcome to Gavin Chen's rpn calculator!\n");
    //begin unit testing
    float result;
    struct Stack values;
    short int test[3];

    /******* test StackInit *******/
    StackInit(&values);
    if (sizeof (values.stackItems) / sizeof (values.stackItems[0]) == STACK_SIZE
	    && values.currentItemIndex == -1) {
	printf("StackInit is functional\n");
    } else {
	printf("StackInit is not functioning\n");
    }

    /******* test StackPush *******/
    StackPush(&values, 6);
    if (values.currentItemIndex == 0
	    && values.stackItems[values.currentItemIndex] == 6) {
	printf("StackPush is functional\n");
    } else {
	printf("StackPush is not functioning\n");
    }

    /******* test StackPop *******/
    StackPop(&values, &result);
    if (values.currentItemIndex == -1 && result == 6) {
	printf("StackPop is functional\n");

    } else {
	printf("StackPop is not functioning\n");
    }

    /******* test StackIsEmpty *******/
    if (StackIsEmpty(&values) == SUCCESS) {
	printf("StackIsEmpty (no values) is functional\n");
    } else {
	printf("StackIsEmpty (no values) is not functioning\n");
    }
    values.currentItemIndex = 0;
    values.initialized = STANDARD_ERROR;
    if (StackIsEmpty(&values) == SUCCESS) {
	printf("StackIsEmpty (not initialized) is functional\n");
    } else {
	printf("StackIsEmpty (not initialized) is not functioning\n");
    }
    values.initialized = SUCCESS;

    /******* test StackIsFull *******/
    values.currentItemIndex = STACK_SIZE + 1;
    if (StackIsFull(&values) == SUCCESS) {
	printf("StackFull is functional\n");
    } else {
	printf("StackFull is not functioning\n");
    }

    /******* test StackGetSize *******/
    values.initialized = STANDARD_ERROR;
    test[0] = StackGetSize(&values);
    StackInit(&values);
    test[1] = StackGetSize(&values);
    StackPush(&values, 4);
    test[2] = StackGetSize(&values);
    if (test[0] == SIZE_ERROR && test [1] == 0 && test[2] == 1) {
	printf("StackGetSize is functional\n");
    } else {
	printf("StackGetSise is not functioning\n");
    }



    /******************************** begin rpn code *******************************/
    while (1) {
	StackInit(&values);
	int operations [STACK_SIZE], j, i, check = 0;
	char input[STACK_SIZE * 2];
	char p[60], *token;

	printf("Hello User! I welcome you to my rpn calculator program!\n");
	printf("now please input an operation in rpn notation: \n");

	printf("Please enter floats and +-*/ in RPN format: \n");
	fgets(p, 100, stdin);
	token = strtok(p, "\0");
	if (strspn(token, "0123456789.") != STANDARD_ERROR) {
	    StackPush(&values, atof(token));
	}
	for (j = 0; StackIsFull(&values) != SUCCESS && input[i] != NULL; i++) {
	    token = strtok(NULL, "\0");
	    if (strspn(token, "0123456789.") != STANDARD_ERROR && check != 1) {
		StackPush(&values, atof(token));
	    } else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0
		    || strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
		operations[j] = (int) *token;
		j++;
		//stores operations from bottom up
		//e.g if first operation is + then intput[0] is +
		check = 1;
	    } else if (check == 1) {
		printf("You put a number/invalid char after the operations! Thats not rpn format!\n"
			"PUT IT IN VALID RPN FORMAT!\n");
	    } else {
		printf("your string contains incorrect characters!\n");
	    }
	}
	if (StackIsFull(&values) == SUCCESS) {
	    printf("you have too many numbers, dumbass\n"); //take out dumbass before subbmitting
	}

	float value1, value2;
	for (i = 0; i <= sizeof (operations) / sizeof (operations[0]); i++) {
	    if (StackIsEmpty(&values) == SUCCESS) {
		printf("stack is empty buddy\n");
		values.initialized = STANDARD_ERROR;
		break;
	    } else if (StackIsFull(&values) == SUCCESS) {
		printf("stack is too full buddy\n");
		values.initialized = STANDARD_ERROR;
		break;
	    }
	    StackPop(&values, &value1);
	    StackPop(&values, &value2);
	    switch (operations[i]) {
	    case '+':
		result = value1 + value2;
		break;
	    case'-':
		result = value1 - value2;
		break;
	    case '/':
		result = value1 / value2;
		break;
	    case '*':
		result = value1 * value2;
		break;
	    default:
		printf("no valid operation detected");
		break;
	    }

	    StackPush(&values, result);
	    printf("there are %d numbers left in the stack", StackGetSize(&values));

	}
	printf("the answer to your query is %f", (double) values.stackItems[values.currentItemIndex]);
	/*************************************************************************************************/

	// You can never return from main() in an embedded system (one that lacks an operating system).
	// This will result in the processor restarting, which is almost certainly not what you want!
    }
}

/**
 * Extra Credit: Define ProcessBackspaces() here - This function should read through an array of
 * characters and when a backspace character is read it should replace the preceding character with
 * the following character. It should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings that are at
 * least 256 characters in length.
 * @param rpn_sentence The string that will be processed for backspaces. This string is modified in
 *                     place.
 * @return Returns the size of the resultant string in `rpn_sentence`.
 */
int ProcessBackspaces(char *rpn_sentence)
{
    return 0;
}




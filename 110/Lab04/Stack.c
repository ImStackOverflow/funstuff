#include "Stack.h"
//stack size is 20

void StackInit(struct Stack *stack)
//makes an array of size STACK_SIZE
//sets the current item index to -1
{
    stack->currentItemIndex = -1;
    stack->initialized = SUCCESS;

}

int StackPush(struct Stack *stack, float value)
//sets value to current item index, increments item index after push
//checks that item index is not exceeded
{
    stack->currentItemIndex++;
    if (stack->currentItemIndex <= STACK_SIZE - 1) {
	stack->stackItems[stack->currentItemIndex] = value;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }

}

int StackPop(struct Stack *stack, float *value)
//sets current item in stack to value of pointer *value
//makes sure that stack is between size 19 and 1
//returns the answer (*vlaue) as a pointer ergo must use it as a pointer
{
    short outcome;
    if (stack->currentItemIndex <= STACK_SIZE - 1
	    && stack->currentItemIndex >= 0) {
	*value = stack->stackItems[stack->currentItemIndex];
	outcome = SUCCESS;
    } else {
	outcome = STANDARD_ERROR;
    }
    stack->currentItemIndex--;
    return outcome;
}

int StackIsEmpty(const struct Stack *stack)
//checks if stack is empty or not yet initialized
//returns 1 if empty\not initialized 
//returns 0 if everything is fine
{
    if (stack->currentItemIndex == -1
	    || stack->initialized != SUCCESS) {
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }
}

int StackIsFull(const struct Stack *stack)
//checks if stack is full
//returns 1 if item index is one over max
//returns 0 if everything is fine
{
    if (stack->currentItemIndex == STACK_SIZE + 1) {
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }
}

int StackGetSize(const struct Stack *stack)
{
    short i;
    if (stack->initialized != SUCCESS) {
	return SIZE_ERROR;
    } else if (stack->currentItemIndex == -1) {
	return 0;
    } else {
	i = stack->currentItemIndex + 1;
	return i;
    }
}




#include "LinkedList.h"
#include "BOARD.h"
#include <stdlib.h>
#include <ctype.h>

ListItem *LinkedListNew(char *data)
{
    ListItem *NewList = malloc(sizeof (ListItem));
    if (NewList) { //check that malloc worked
	NewList->data = data;
	NewList->nextItem = NULL;
	NewList->previousItem = NULL;
	return NewList;
    } else {//if malloc didnt work then throw error
	return STANDARD_ERROR;
    }
}

char *LinkedListRemove(ListItem *item)
{
    if (item) { //if item isnt null
	char *data = item->data;
	ListItem *hold2 = item->nextItem;
	ListItem *hold1 = item->previousItem;
	free(item);
	if (hold1 == NULL) { //if list was at head set next listItem as head
	    item = hold2;
	    item->previousItem = hold1;
	} else if (hold2 == NULL) {//if list was foot set previous listItem as foot
	    item = hold1;
	    item->nextItem = hold2;
	} else { //if list was in middle than stich together the sides
	    item = hold2;
	    item->previousItem = hold1;
	    item = hold1;
	    item->nextItem = hold2;
	}
	return data;
    } else {
	return STANDARD_ERROR;
    }
}

int LinkedListSize(ListItem *list)
{
    int elements = 1;
    LinkedListGetFirst(list);
    while (list->nextItem != NULL) {//iterate through 
	elements++;
	list = list->nextItem;
    }
    return elements;

}

ListItem *LinkedListGetFirst(ListItem *list) //returns pointer
{
    if (list) {
	while (list->previousItem != NULL) {//set list to beginning
	    list = list->previousItem;
	}
    }
    return list;
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *Newlist = LinkedListNew(data);
    if (Newlist) {
	if (item->nextItem == NULL) {//if previous listItem was foot
	    //insert new item and suture to previous item
	    Newlist->previousItem = item;
	    Newlist->nextItem = item->nextItem;
	    item->nextItem = Newlist;
	} else {
	    //insert new item and suture to surrounding lists
	    ListItem *hold = item->nextItem;
	    Newlist->previousItem = item;
	    Newlist->nextItem = item->nextItem;
	    item->nextItem = Newlist;
	    item = hold;
	    item->previousItem = Newlist;
	}
	return Newlist;
    } else {
	return NULL;
    }

}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    if (firstItem && secondItem) {//make sure both items are valid
	char *hold = firstItem->data;
	firstItem->data = secondItem->data;
	secondItem->data = hold;
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }

}

int LinkedListSort(ListItem *list)
{
    char *p1, *p2;//for derefrencing pointers
    list = LinkedListGetFirst(list);
    //make temporary list for sorting
    ListItem *list2;
    if (list) {
	int i, j, z = LinkedListSize(list);
	//sort by letters
	for (i = 0; i <= z - 2; i++) {
	    list = LinkedListGetFirst(list);
	    list2 = list->nextItem;
	    for (j = i + 1; j <= (z - 1); j++) {
		if (list2->nextItem == NULL) { //break once reach end
		    LinkedListSwapData(list, list2);
		    break;
		}
		if (list->data == NULL && list == list) {
		    list = list2;
		    list2 = list2->nextItem;
		    continue;
		} else if (list->data == NULL || list2->data == NULL) { //put null at beginning of list
		    if (list->data == NULL) {
			ListItem *hold1 = list->nextItem;
			ListItem *list3 = LinkedListCreateAfter(LinkedListGetFirst(list), LinkedListRemove(list));
			LinkedListSwapData(list3, LinkedListGetFirst(list));
			list = hold1;
		    } else {
			ListItem *hold2 = list2->nextItem;
			ListItem *list3 = LinkedListCreateAfter(LinkedListGetFirst(list2), LinkedListRemove(list2));
			LinkedListSwapData(list3, LinkedListGetFirst(list2));
			list2 = hold2;
		    }
		} else {//if not null 
		    p1 = list->data; //derefrence pointers for comparison
		    p2 = list2->data;
		    if (strcmp(p1, p2) > 0) {
			LinkedListSwapData(list, list2);
		    }

		    list = list2;
		    list2 = list2->nextItem;
		}
	    }
	}
	return SUCCESS;
    } else {
	return STANDARD_ERROR;
    }

}

int LinkedListPrint(ListItem *list)
{
    int i, j = LinkedListSize(list);
    list = LinkedListGetFirst(list);
    if (LinkedListSize(list) == 1) { //formating if only one listItem
	printf("(%s)\n", list->data);
	return SUCCESS;
    } else if (list) { //if more than one
	printf("(%s, ", list->data);
	for (i = 1; i < j - 1; i++) {
	    list = list->nextItem;
	    printf("%s, ", list->data);
	}
	list = list->nextItem;
	printf("%s)\n", list->data);
	return SUCCESS;
    } else {//any error
	printf("there are no elements in the list\n");
	return STANDARD_ERROR;
    }

}
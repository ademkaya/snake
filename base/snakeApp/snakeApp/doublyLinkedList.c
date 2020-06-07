#include "doublyLinkedList.h"

static doublyLinkedList_Typedef* statPtr;

bool AddNode(doublyLinkedList_Typedef** ptr, void* data);

bool AddNode(doublyLinkedList_Typedef** ptr,void* data) {
	doublyLinkedList_Typedef* leftHolder = NULL;
	bool retVal = true;

	if (*ptr==NULL) {
		*ptr = calloc(1, sizeof(doublyLinkedList_Typedef));
		if (!(*ptr))
			retVal = false;
		else
			statPtr = *ptr;
			(*ptr)->data = data;
	} else {
		leftHolder = *ptr;
		while (leftHolder->right) {
			leftHolder = leftHolder->right;
		}
		leftHolder->right = calloc(1, sizeof(doublyLinkedList_Typedef));
		if (!(leftHolder->right))
			retVal = false;
		else
		(leftHolder->right)->left = leftHolder;
		(leftHolder->right)->data = data;
	}

	return retVal;
}
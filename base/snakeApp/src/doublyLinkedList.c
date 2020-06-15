#include "doublyLinkedList.h"

static doublyLinkedList_Typedef** statPtr;

bool AddNode(doublyLinkedList_Typedef** ptr, void* data);
void DeleteSiblings(doublyLinkedList_Typedef** node,bool firstCall);

bool AddNode(doublyLinkedList_Typedef** ptr,void* data) {
	doublyLinkedList_Typedef* leftHolder = NULL;
	bool retVal = true;

	if (*ptr==NULL) {
		*ptr = calloc(1, sizeof(doublyLinkedList_Typedef));
		if (!(*ptr)) {
			retVal = false;
		}else {
			statPtr = ptr;
			(*ptr)->data = data;
		}
	}
	else {
		leftHolder = *ptr;
		while (leftHolder->right) {
			leftHolder = leftHolder->right;
		}
		leftHolder->right = calloc(1, sizeof(doublyLinkedList_Typedef));
		if (!(leftHolder->right)){
			retVal = false;
		} else {
			(leftHolder->right)->left = leftHolder;
			(leftHolder->right)->data = data;
		}
	}

	return retVal;
}

void DeleteSiblings(doublyLinkedList_Typedef** node,bool firstCall) {
	static doublyLinkedList_Typedef* head = NULL;
	if (firstCall) {
		head = *node;
	}

	if ((*node)->right) {
		DeleteSiblings(&((*node)->right),false);
		if (*node != head) {
			free(*node);
			*node = NULL;
		}
	} else {
		if (*node != head) {
			free(*node);
			*node = NULL;
		}
		return;
	}


}
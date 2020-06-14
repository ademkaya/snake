/*
 * File:   doublylinkedlist.h
 * Author: Adem
 *
 * Started on Jun , 2020, 6:11 PM
 */

#ifndef __DOUBLYLINKEDLIST_H__
#define __DOUBLYLINKEDLIST_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

typedef struct node {	
	void* data;
	struct node* right;
	struct node* left;
}doublyLinkedList_Typedef;


bool AddNode(doublyLinkedList_Typedef** listPtr, void* data);


#ifdef __cplusplus
}
#endif
#endif /* __DOUBLYLINKEDLIST_H__ */
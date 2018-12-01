#ifndef ISA_LINKED_LIST_H
#define ISA_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "our_list.h"


typedef struct Node {
	unsigned int line_number;
	char* label_name;
	struct Node* next; /* Pointer to next node in the list */
} Node;

/* a linked list struct */
typedef struct List {
	Node* head; /* this pointer points on the head of the list */
	size_t size;
} List;

/*
* initList
*
*  This function initializes new list structure, with a single dummy node (has a -1 value for
*  number of moves. this dummy node will be useful for detecting if we got to the beginning
*  of the list.
*  @return - pointer to the new list
*/
List* initList();

/**
* This function creates a new node with a given key and value.
* @param key - The key to be given to the new node
* @param value - The value to be given to the new node
* @return - A pointer to the new node created
*/
Node* create_node(char* label_name, unsigned int line_number);

/**
* This function iterates over the linked list to find the value of a node given a key
* @param list - The list to find the node in
* @param key - The key of the node to look for
* @return value - If a node with the given key is found on the list
* -1 - If list = NULL or if the list doesn't contain a node with the given key
*/
int find_node(List* list, char* label_name);

/*
* addMove
*
*  The function adds a new node (which was already prepared) to the list
*  @param undoList - pointer to the current list
*  @param newNode - pointer to a new node (which was already created and filled)
*  @return -
*/
void addNode(List* list, char* label_name, unsigned int line_number);

/*
* destroyList
*
*  This function clears the entire list from memory.
*  @param undoList - pointer to the current list
*  @return -
*/
void destroyList(List* list);

#endif //ISA_LINKED_LIST_H
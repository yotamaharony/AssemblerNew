/*
* list Module
*
*  This module describes the doubly linked list structure which we are using in order to handle
*  undo and redo calls. Every time the board is changed, a new node which describes the change
*  is added to the structure.
*  The functions here are directly related to the structure.
*  Memory management of the stack is also done here.
*/

#include "our_list.h"


/* Public methods: */

/*
* initList
*
*  This function initializes new list structure, with a single dummy node (has a -1 value for
*  number of moves. this dummy node will be useful for detecting if we got to the beginning
*  of the list.
*  @return - pointer to the new list
*/
List* initList()
{
	List* newList = malloc(sizeof(List));
	if (!newList)
	{
		printf("Error: malloc has failed\n");
		exit(0);
		return NULL;
	}
	newList->size = 0;
	newList->head = NULL;
	return newList;
}

Node* create_node(char* label_name, unsigned int line_number) {
	Node* node = (Node*)malloc(sizeof(Node));
	char* new_name = (char*)malloc(sizeof(char) * (strlen(label_name) + 1));
	if (node == NULL) {
		printf("Error: malloc has failed\n");
		exit(0);
		return NULL;
	}
	node->next = NULL;
	node->line_number = line_number;
	strcpy(new_name, label_name);
	new_name[strlen(new_name) - 1] = '\0';
	node->label_name = new_name;
	return node;
}

int find_node(List* list, char* label_name) {
	if (list == NULL) {
		return -1;
	}
	Node* node = list->head;
	while (node) {
		if (strcmp(node->label_name, label_name) == 0) {
			return node->line_number;
		}
		node = node->next;
	}
	return -1;
}


void addNode(List* list, char* label_name, unsigned int line_number) {
	if (list == NULL) {
		return;
	}
	Node* node = create_node(label_name, line_number);
	if (node == NULL) {
		return;
	}
	if (list->head == NULL) {
		list->head = node;
		list->size++;
		return;
	}
	node->next = list->head;
	list->head = node;
}

void destroyList(List* list) {
	if (list == NULL) {
		return;
	}
	Node* temp = list->head;
	while (temp) {
		list->head = temp->next;
		free(temp->label_name);
		free(temp);
		temp = list->head;
	}
	free(list);
}
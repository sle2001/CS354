/******************************************************************************
 * @file: ll_functions.c
 *
 * sle6@wisc.edu
 * sle6
 * 9082264376
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Steven Le (sle6@wisc.edu)
 * @modified: 7/11/22 Steven Le (sle6@wisc.edu)
 *****************************************************************************/

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll_structs.h"

#include "ll_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function allocates all the memory needed for created a new linked list,
 * and initializes any necessary fields of the LL struct. The implementation 
 * of this function directly depends on how you design your LL struct. 
 *
 * @return A valid pointer on success, NULL on failure
 */
LL *LL_Init() {
	LL *L = malloc(sizeof(LL)); // Initialize head pointer
	// Check if head is NULL
	if(!L) {
		return NULL;
	}
	L->head = NULL;
	L->numNodes = 0;
    return L;    
}

/* 
 * Insert the (key, value) pair into the linkeded list. If a node with a key 
 * that matches the argument key, the current value stored with that key should
 * be overwrriten by the data in the value argument. Note, you will likely 
 * need to free the old memory or reallocate the amount of memory. Hint: You 
 * will likely also need to store the value of n for later use. 
 *
 * Note: Overwriting the value for an existing value is considered a success. 
 *
 * @param L A pointer to a Linked List struct (may be NULL)
 * @param key The key identifier for the data being inserted
 * @param payload A pointer to the data to write into the node
 * @param n The number of bytes that param value is valid for 
 * @return 1 on success, 0 on failure
 */
int LL_Insert(LL *L, size_t key, char *value, size_t n) {
        if(L == NULL || value == NULL) {
		return 0;
	}
	
	//Create a new node
        node *newNode = malloc(sizeof(node));

	// Check if malloc failed
	if(!newNode) {
		return 0;
	}

	// Insert values
        newNode->key = key;
        newNode->numBytes = n;
	newNode->value = malloc(n*sizeof(char));
	
	// Check if malloc failed
	if(newNode->value == NULL) {
		return 0;
	}

	// Insert values
	for(int i = 0; i < n; ++i) {
		newNode->value[i] = value[i];
	}
        newNode->next = NULL;
	
	// If it's the first node
	if(L->numNodes == 0) {
		L->head = newNode;
		L->numNodes = 1;
		return 1;
	}

	// Insert the node into either the end of the list or replace the value if key matches
        node *currentNode = L->head;
	// Check if the key already exists in the list
	if(currentNode->key == key) {
		// Free
		free(currentNode->value);
		free(newNode->value);
		free(newNode);

		// Malloc
		currentNode->value = malloc(n*sizeof(char));

		// Check if malloc failed
		if(currentNode->value == NULL) {
			return 0;
		}

		// Insert values
		for(int i = 0; i < n; ++i) {
			currentNode->value[i] = value[i];
		}
		currentNode->numBytes = n;
		
		return 1;
	}

	// Tranverse through the list
	while(currentNode->next != NULL) {
		// Check if the key already exists in the list
		if(currentNode->key == newNode->key) {
			// Free
			free(currentNode->value);
			free(newNode->value);
			free(newNode);
                
			// Malloc
			currentNode->value = malloc(n*sizeof(char));

	                // Check if malloc failed
        	        if(currentNode->value == NULL) {
        	                return 0;
	                }

			// Insert values
        	        for(int i = 0; i < n; ++i) {
	                        currentNode->value[i] = value[i];
               		 }
			currentNode->numBytes = n;
			
			return 1;
		}
		currentNode = currentNode->next; // Move on to next node
	}

		// Check if the key already exists in the list
		if(currentNode->key == key) {
			// Free
			free(currentNode->value);
			free(newNode->value);
			free(newNode);

			// Malloc
			currentNode->value = malloc(n*sizeof(char));
		
			// Check if malloc failed
	                if(currentNode->value == NULL) {
	                        return 0;
        	        }

			// Insert values
			for(int i = 0; i < n; ++i) {
                        currentNode->value[i] = value[i];
			}
			currentNode->numBytes = n;
			
			return 1;
		}


	currentNode->next = newNode; // Insert node into the end of the list
	L->numNodes = L->numNodes + 1;
	// Check if it inserted the node correctly
	if((currentNode->next->value != newNode->value) && (currentNode->next->key != newNode->key)) {
		return 0; // Didn't insert
	}
    	
	return 1;
}

/* 
 *
 * Getter function to return the size of the linked list.
 *
 * @return The number of nodes in the linked list struct.
 */
size_t LL_Size(LL *L) {
      	return L->numNodes;
}

/* 
 * Function should fill in the to_fill argument with the bytes of the value
 * found at node whose key is equal to the key argument. If no node in the 
 * linked list has a key value equal to the key argument, no bytes should be 
 * written to the to_fill argument, and you should return 0.
 *
 * This function should detect if the value in the linked list is too large to
 * fit into the to_fill argument. In such a case, no bytes should be written,
 * and this function should return 0.
 *
 * @param L A pointer to a Linked List struct (may be NULL)
 * @param key The search key
 * @param to_fill A pointer to an externally allocated array to be filled in
 * @param n A pointer initally set to the size of to_fill and to be set to 
 *          the actual number of bytes written upon success
 * @return 1 on success, 0 on failure
 */
int LL_Get(LL *L, size_t key, char *to_fill, size_t *n) {
    	// Check if pointer to LL is null
	if(L->head == NULL || L == NULL || to_fill == NULL || n == NULL) {
		return 0;
	}

	node *current = L->head;
	if(current->key == key) {
		size_t num = current->numBytes;
		if(num <= *n) {
			for(int i = 0; i < current->numBytes; ++i) {
				to_fill[i] = current->value[i];
			}
			*n = current->numBytes;
			return 1;
		}
		return 0;
	}

	while(current->next != NULL) {
		if(current->key == key) {
			if(current->numBytes <= *n) {
				for(int i = 0; i < current->numBytes; ++i) {
					to_fill[i] = current->value[i];
				}
				*n = current->numBytes;
				return 1;	
			}
			else {
				return 0;
			}
		}
		current = current->next;
	}	

	if(current->key == key) {
                size_t num = current->numBytes;
                if(num <= *n) {
                        for(int i = 0; i < current->numBytes; ++i) {
                                to_fill[i] = current->value[i];
                        }
                        *n = current->numBytes;
                        return 1;
                }
                return 0;
        }

	return 0;
}

/* 
 * Function should remove a node from the liked list if the key exists in such 
 * a node. When the node is removed, all memory allocated for that node should
 * be freed. 
 *
 * @param L A pointer to a Linked List struct (may be NULL)
 * @param key The search key
 * @return 1 on successful removal, 0 on failure
 */
int LL_Remove(LL *L, size_t key) {
	// Check if the pointer to the  LinkedList is null
	if(L == NULL) {
		printf("Null was ran");
		return 0;
	}
	
	// Create a node pointing at the beginning of list
	node *temp = L->head, *prev;

	// Check if the key is the first node
	if (temp != NULL && temp->key == key) {
		L->head = temp->next;
		free(temp->value);
		free(temp);
		L->numNodes--;
		return 1;
	}
	
	// Find the node to remove
	while(temp != NULL && temp->key != key) {
		prev = temp;
		temp = temp->next;
	}

	// If the key wasn't in the node
	if(temp == NULL) {
		return 0;
	}

	// Unlink the node from linked list
	prev->next = temp->next;

	free(temp->value);
	free(temp);
	L->numNodes--;

	return 1;
}

/* 
 * Function to completely free a linked list. 
 *
 * @param L A pointer to the linked list to be freed (may be NULL)
 */
void LL_Free(LL *L) {
	if(L == NULL) {
	}
	else {
		node *current = L->head;
		node *next;

		while(current != NULL) {
			next = current->next;
			free(current->value);
			free(current);
			current = next;
		}
		free(L);
	}
}

/******************************************************************************
 * @file: ll_structs.h
 *
 * Header file for data structures to implement a user defined linked list.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 7/10/22 Steven Le (sle6@wisc.edu
 *
 *****************************************************************************/

#ifndef __LL_STRUCTS_H__
#define __LL_STRUCTS_H__

// Add whatever struct definitions you may need here
typedef struct node {
        size_t key;
        char *value;
	struct node *next;
        size_t numBytes;
} node;

typedef struct linked_list {
    // Todo fill this with whatever data you need
    node *head;
    size_t numNodes;
} LL;

#endif //__LL_FUNCTIONS_H__

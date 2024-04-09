/******************************************************************************
 * @file: tester.c
 *
 * Main file that tests are performed.
 *
 * @creator: Steven Le (sle6@wisc.edu)
 * @modified: 7/11/22 Steven Le (sle6@wisc.edu)
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

int main(int argc, char *argv[]) {
    // Verify command line parameters
    if(argc != 1){
        printf("expected usage: %s\n", argv[0]); 
        exit(1);
    }
    
    HT *T = HT_Init();
    if (!T) {
        printf("Error: Unable to allocate memory for Hash Table!\n");
        exit(1);
    }
    if(!HT_Put(T, 42, "hi", 3)) {
        printf("Error: Failed to put new value into hash table!\n");
        exit(1);
    }
    size_t len1 = strlen("test")+1;
    if(!HT_Put(T, 50, "test", 5)) {
	    printf("Error: Failed to put another new value into hash table!\n");
	    exit(1);
    }
    size_t len = strlen("hello") + 1;
    if(!HT_Put(T, 42, "hello", len)) {
        printf("Error: Failed to detect exisiting key!\n");
        exit(1);
    }
    char buf[10];
    size_t size = 10;
    if(!HT_Get(T, 42, buf, &size)) {
        printf("Error: Failed to get value that was just put!\n");
        exit(1);
    }
    if(size != len) {
        printf("Error: n incorrectly set by HT_Get!\n");
        exit(1);
    }
    char cmp[6] = "hello";
    for(size_t i = 0; i < len; i++) {
        if(buf[i] != cmp[i]) {
            printf("Error: Read char %c but should've been %c!\n",
                    buf[i], cmp[i]);
            exit(1);
        }
    }
    char buf1[30];
    size_t size1 = 30;
    if(!HT_Get(T, 50, buf1, &size1)) {
	    printf("Error: Failed to get value that was just put (added)!\n");
	    exit(1);
    }
    if(size1 != len1) {
	    printf("Error: n incorrect set by HT_Get!\n");
    }
    char cmp1[5] = "test";
    for(size_t i = 0; i < len1; ++i) {
	    if(buf1[i] != cmp1[i]) {
		    printf("Error: Read char %c but should've been %c (added)!\n", buf1[i], cmp1[i]);
	    }
    }
    HT_Free(T); 
    printf("Success! Make sure to check for memory leaks!\n");
    return 0;
}


/******************************************************************************
 * @file: mem.c
 *
 * sle6
 * Steven Le
 * 908 226 4376
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: Steven Le (sle6@wisc.edu)
 * @modified: 8/5/22
 *****************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "header.h"
#include "mem.h"

// Set this to 1 to enable dbgprintf  and dbgassert statements, make sure to 
// set it back to 0 before submitting!
#define DEBUG               1 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgassert(...)      if (DEBUG) { assert(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Global Variables
 *****************************************************************************/
void *heap_start;
size_t heap_size;
void *heap_end;
/******************************************************************************
 * Memory Allocator functions
 *****************************************************************************/

/*
 * This function initializes the heap space for future calls to Mem_Alloc and 
 * Mem_Free. You may safely assume that this function is only called once in 
 * a given program.
 *
 * @param Heap_Start : A pointer to the start of the heap space
 * @param Heap_Size : The size the heap
 * @return void
 */

void Mem_Init(void *Heap_Start, size_t Heap_Size) {

    // Register the start of the heap to the global variable
    heap_start = Heap_Start;

    // Register the size of the heap to the global variable
    heap_size = Heap_Size;

    /* BEGIN MODIFYING CODE HERE */

    // (Extra Credit) Set up prologue blocks
    unsigned long long Prologue_Num = ((unsigned long long) Heap_Start & ~0x0FULL); // Get num to align with 16 bytes
    Header *Prologue_Header = (Header *) (Prologue_Num - sizeof(Header)); // Make a header pointer pointing to a memory that ends with c
    
    *Prologue_Header = 17; // Set the prologue header equal to 17 to show its allocated and block size

    Prologue_Num = ((unsigned long long) Heap_Start & ~0x0FULL) + 16; // Go to the first user  header
    Footer *Prologue_Footer = (Footer *) (Prologue_Num - sizeof(Footer)*2); // Make the footer pointer point to the footer of prologue

    *Prologue_Footer = *Prologue_Header; // Set the footer equal to the header
	
    // (Extra Credit) Set up epilogue block
    unsigned long long Epilogue_Num = ((unsigned long long) Heap_Start) + Heap_Size; // Move num to the end of heap
    Epilogue_Num = Epilogue_Num & ~0x0FULL; // Make it align to 16 bytes
    Header *Epilogue_Header = (Header *) (Epilogue_Num - sizeof(Header)); // Move header pointer to where pointer has to be

    *Epilogue_Header = 0x1; // Set Header value to 0x1
    
    Epilogue_Num += 16 - sizeof(Footer); // Move num to where footer would be
    Footer *Epilogue_Footer = (Footer *) Epilogue_Num; // Set footer pointer at where num is in memory

    *Epilogue_Footer = *Epilogue_Header; // Set the value of footer equal to the header


    // (Mandatory) Set up heap space
    unsigned long long Heap_End_Num = ((unsigned long long) Heap_Start + Heap_Size);
    heap_end = (void *) Heap_End_Num;
    /* Your first task is initialize the header for the heap. The heap may 
     * contain garbage values, your job is to mark the first header to denote
     * that heap can be treated as one large free block. To do so, you can use
     * the following steps:
     *
     * 1) Find the pointer that will be returned on the first call to malloc.
     *    Remember, this pointer must be aligned to a 16 byte boundary.
     * 2) Subtract sizeof(Header) bytes to get a pointer to the first header
     * 3) Set this header to the correct value. Ensure the LSB is 0 to mark
     *    the block as free.
     * 4) (Optional) if you are using footers, ensure you set the last 
     *    sizeof(Header) bytes to the same value as the header.
     */
	unsigned long long Header_Num = ((unsigned long long) Heap_Start & ~0x0FULL) + 16; // Align num to 16 bytes
	Header *First_Header = (Header *) (Header_Num - sizeof(Header)); // Set the first header where num is

	*First_Header = Heap_Size; // Set the block size to heap size
	*First_Header = *First_Header & (~1); // Make sure that the LSB is 0 to show it's free

	Header_Num += 16 - sizeof(Footer); // To get num to the footer
	Footer *First_Footer = (Footer *) Header_Num; // Create a footer

	*First_Footer = *First_Header; // Make value of footer same as header

    /* END MODIFYING CODE HERE */
    return;
}

/*
 * This function  allows a user to request space on the heap. The type of param
 * payload is defined in mem.h and may not be changed. If param payloa
 * d is ever
 * 0, this function should return NULL immediately. 
 *
 * @param payload : The number of bytes the user wants on the heap
 * @return A 16-byte aligned pointer to payload bytes on the heap on success,
 *         NULL on failure
 */
void* Mem_Alloc(Payload payload){
    /* BEGIN MODIFYING CODE HERE */

    // First, verify non-zero payload size
    if(payload == 0) {
	    return NULL;
    }
    // Determine what size block is needed to satisfy this payload request.
    // Remember, user pointers must be 16-byte aligned, and the minimum block
    // size is 16 bytes. 
    int n = 16;
    while(n < (payload + 8)) {
	    n += 16; // Add 16 bytes each time for memory block alignment
    }

    // Search the heap space for a free block that can satisfy the request.
    unsigned long long Header_Num = ((unsigned long long) heap_start & ~0x0FULL) + 16; // Align num to 16 bytes
    Header_Num -= sizeof(Header);
    
    Header *New_Header = (Header *) (Header_Num); // Set the first header where the first header is

        // Search should be done in address order.
	// While the LSB in the header is 1  OR the size of the block is too small for payload OR it reached past the allocated heap size
	while((*New_Header & (0x1)) || (*New_Header < n)) {
	       // Checks if there is no more space for the payload
	        if(heap_end <= (void *) New_Header) {
                	return NULL;
        	}

		// Check if the header is allocated
		if(*New_Header & (0x1)) {
			Header_Num += *New_Header - 1; // Removed LSB so Header_Num can go to the next Header
		}
		else {
			Header_Num += *New_Header;
		}

		New_Header = (Header *) (Header_Num); // Make new header = to the current header	
	}
	
        // if found, determine in the block can be split
	if((*New_Header & ~(0x01)) && (*New_Header >= n)) {
            // if split is possible, split block and set headers
	    if(*New_Header > n) {
		    int Old_Block_Size = *New_Header;
	    
		    *New_Header = n | 1; // Set the new header equal to the size of block size and make LSB 1

		    Header_Num += n - sizeof(Footer); // Increment the Header_Num to the footer of the block
		    Footer *New_Footer = (Footer *) (Header_Num); // Make a pointer footer where Header_Num is

		    *New_Footer = *New_Header; // Make the value of the new footer same as the header

		    Old_Block_Size -= *New_Header - 1; // Get the new block size for free space and remove the LSB of 1
		    
		    Header *New_Free_Header = (Header *) (Header_Num + sizeof(Footer)); // Make the new free header
		    *New_Free_Header = Old_Block_Size; // Set the value of the new free header same as the old header
		    *New_Free_Header = *New_Free_Header & (~1); // Make LSB 0
	    
		    Header_Num += Old_Block_Size - sizeof(Footer); // Make it point to the footer of the free block
		    Footer *New_Free_Footer = (Footer *) (Header_Num); // Make the pointer footer where Header_Num is

		 *New_Free_Footer = *New_Free_Header; // Set the value of the new free footer same as the header
		 
		 void *pnter = New_Header + (sizeof(Header)/4); // Get the pointer to equal to the memory after header
	
		 return pnter;
		}

            // if split is not possible, allocate directly into block
	    if(*New_Header == n) {
		*New_Header = n | 1; // Set the new header equal to the size of block size and make LSB 1

		Header_Num += n - sizeof(Footer); // Increment the Header_Num to the footer of the block
		Footer *New_Footer = (Footer *) (Header_Num); // Make a pointer footer where Header_Num is


		*New_Footer = *New_Header; // Make the value of the new footer same as the header

		void *pnter = New_Header + (sizeof(Header)/4);

		return pnter;
	    }
	}	
        // else retrun NULL
	else {
		return NULL;
	}
	

    return NULL;
}


/*
 * This function  allows a user to tell the memory allocator that they finished
 * using space that they had requested on the heap.
 *
 * @param ptr: A pointer
 * @return 0 on error, 1 on success 
 */
int Mem_Free(void *ptr) {
    // First, search through the allocated blocks to see if these ptr is indeed
    // one that was returned by a call to Mem_Alloc
    
    // Check if ptr is NULL
    if(ptr == NULL) {
	    return 0;
    }

    // Check if ptr is before the start of heap
    if(ptr < heap_start) {
	    return 0;
    }

    // Check if ptr is after the heap
    if(ptr > (heap_start + heap_size)) {
	    return 0;
    }

    // Check if the ptr is pointing somewhere that is not suppose to point in the heap (i.e. interior pointer)    
    if(((unsigned long long) ptr & (0x0F))) {
            return 0;
    }

    unsigned long long Current_Num = ((unsigned long long) heap_start & ~0x0FULL) + 16; // Make Current_Num aligned 16 bytes
    void *Current_Ptr = (void *) Current_Num; // Make the current pointer at where the first user pointer would be (if ran mem_alloc)

    Current_Num -= sizeof(Header); // Get the header mem
    Header *Current_Header = (Header *) (Current_Num); // Make pointer to point to the header of Current_Ptr

    Header *Prev_Header = (Header *) (Current_Num); // Set a prev header so we can check if previous space was free for coalescing

    // While loop so we can find the pointer that we are looking for
    while(ptr != Current_Ptr || (heap_size > Current_Num)) {
	    // Check if ptr is pointing somwhere that it is not suppose to
	    if(Current_Ptr > ptr) {
		    return 0;
	    }
	    // Check if the current block is free
	    if((*Current_Header & 1) == 0) {
	    	Current_Num += *Current_Header; // Move to next block

		Prev_Header = Current_Header; // Make the previous header equal to current header
		Current_Header = (Header *) (Current_Num); // Make the current header equal to the next block
		printf("Prev_Header = %p, Current_Header %p\n", Prev_Header, Current_Header);
		Current_Ptr = (void *) (Current_Num + sizeof(Header)); // Make the pointer equal to the next block user pointer
	    }
	    else {
		    Current_Num += *Current_Header - 1; // Move to next block (subtract 1 because of allocation)

		    Prev_Header = Current_Header; // Make previous header equal to the current header
		    Current_Header = (Header *) (Current_Num); // Make the current header equal to the next block
		    Current_Ptr = (void *) (Current_Num + sizeof(Header)); // Make the pointer equal to the next block user pointer
	    }
    }

    // If ptr is not in heap, return 0 immediately
    if(ptr != Current_Ptr) {
	    printf("This ran");
	    return 0;
    }
    
    // If ptr is not after a Header, return 0 immediately
    if((Current_Header + (sizeof(Header)/4)) != ptr) {
	    return 0;
    }
    // If the header before ptr is not allocated, return 0 immediately
    if((*Current_Header & 1) == 0) {
	    return 0;
    }
    // Free the block
    *Current_Header -= 1; // Make LSB 0

    // Check if we are freeing the first one
    if(Prev_Header == (Current_Header)) {
	    Current_Header = (Header *) (Current_Num + *Current_Header);
	    if((*Current_Header & 1) == 0) {
	    	*Prev_Header = heap_size; // Make the header equal to heap size
	    }
    }
    else {	    
    	// Coalesce adjacent free blocks
	// Check if the previous header is a free block
    	if(((*Prev_Header & 1) == 0)) {
		    *Prev_Header += *Current_Header; // Coalesce the previous free block and the current block
    	}
    	// Coalesce next block if free
    	Current_Header = (Header *) (Current_Num + *Current_Header); // Make the header equal to the 
    	if((*Current_Header & 1) == 0) {
		    *Prev_Header += *Current_Header;
    	}
    }

    return 1;
}


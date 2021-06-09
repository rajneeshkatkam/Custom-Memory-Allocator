/*
In mm1 implementation:

1. When a request for allocation comes, it first searches for an available free block in the list of blocks using best fit strategy. 
2. If no sufficient size of block is found, a new block is allocated using mem_sbrk(). This block is then added to the list of blocks.
3. On free, two-sided coalescing is performed.
4. The head pointer (free_list_start) and tail pointer of the list is maintained (free_list_end).
5. The insertion takes O(1) time due to the insertion of block at the end of list usign tail pointer. 
6. Searching is done using best fit and takes O(n) to search the list.
7. Each block has its metadata stored in its header: size, is_free, next pointer and previous pointer. It's size is 24 bytes.

 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "CypherX",
    /* First member's full name */
    "Rajneesh Katkam",
    /* First member's email address */
    "rajneeshkatkam@cse.iitb.ac.in",
    /* Second member's full name (leave blank if none) */
    "Sanjna Mohan",
    /* Second member's email address (leave blank if none) */
    "sanjnamohan@cse.iitb.ac.in"
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

//header struct
typedef	struct header_t
{
	struct header_t *next, *prev;
	long long int size, is_free;
} Header;



Header *free_list_start, *free_list_end;


int mm_init(void)
{
	free_list_start=NULL;
	free_list_end=NULL;
    return 0;		//Returns 0 on successfull initialization.
}



// Best fit free list searching function
Header *search_free_list(size_t size)
{
	Header *curr = free_list_start, *best_fit = NULL;
	while(curr) {

	if (curr->is_free && curr->size >= size && (best_fit == NULL || curr->size < best_fit->size))
		{
			best_fit = curr;
		}
		curr = curr->next;
	}
	return best_fit;
}



void *mm_malloc(size_t size)
{	
	if(size <= 0){		// Invalid request size
		return NULL;
	}

	size = ALIGN(size);

	//traversing through the list of blocks to see if any block is present with required size (first fit)
	Header *header = (Header *) search_free_list(size);

	if(header==NULL)
	{
		//if no block is present, request for new block
		int total = sizeof(Header) + size;
		header = mem_sbrk(total);
		header -> is_free=0;
		header -> size=size;
		header -> next = NULL;
		
		//add the new obtained block into the list of blocks
		if(free_list_start == NULL)
		{
			free_list_start = free_list_end = header;
			header->prev=NULL;
		}
		else
		{
			header->prev=free_list_end;
			free_list_end -> next = header;
			free_list_end = header;
		}

		return (void *)(header+1);
	}


	header -> is_free=0;

	if(header->size > size+sizeof(Header)+ALIGNMENT)
	{
		int total = sizeof(Header) + size;
		size_t remaining_size=header->size - total;
		header->size=size;

		Header *new_fragmented_block= (void *)header + total;
		new_fragmented_block->size=remaining_size;
		new_fragmented_block->is_free=1;
		new_fragmented_block->next=header->next;
		if(new_fragmented_block->next)
			new_fragmented_block->next->prev=new_fragmented_block;
		else
			free_list_end=new_fragmented_block;
		
		header->next=new_fragmented_block;
		new_fragmented_block->prev=header;	
	}
	
	return (void *)(header+1);
}



void mm_free(void *ptr)
{
	if (ptr==NULL)
		return;

	Header *header=(Header *)ptr - 1;
	header->is_free = 1;

	// Forward Coalescing
	if(header->next && header->next->is_free)
	{
		header->size+= (header->next->size + sizeof(Header));
			

		if(header->next->next)
		{
			header->next->next->prev=header;
			header->next=header->next->next;
		}
		else
		{
			free_list_end=header;
			header->next=NULL;
		}
	}

	// Backward Coalescing
	if(header->prev && header->prev->is_free)
	{
		header->prev->size+=(header->size + sizeof(Header));

		
		if(header->next)
		{
			header->prev->next=header->next;
			header->next->prev=header->prev;
		}
		else
		{
			free_list_end=header->prev;
			header->prev->next=NULL;
		}
	}
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{	
	size = ALIGN(size); //8-byte alignement	
	
	if(ptr == NULL){			//memory was not previously allocated
		return mm_malloc(size);
	}
	
	if(size == 0){				//new size is zero
		mm_free(ptr);
		return NULL;
	}

	Header *header = (Header *)ptr-1;
	unsigned long int ptr_curr_size=header->size ;

	
	if(ptr_curr_size == size)
		return ptr;


	void *temp_ptr = mm_malloc(size);
	memcpy(temp_ptr, ptr, ((Header *)temp_ptr-1)->size < ptr_curr_size ? ((Header *)temp_ptr-1)->size : ptr_curr_size);

	mm_free(ptr);
	return temp_ptr;
	
}

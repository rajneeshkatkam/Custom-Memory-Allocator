/* Improvements in mm2 over mm1 implementation:

1. Header size reduced from 24 bytes to 16 bytes by removing is_free variable to check block is free or not. Instead, now free checking is done using LSB of the size variable (Header -> actual_size) of the header.
2. Using Modified first fit statergery for better throughput along with fragmentation if needed.
3. Added two way traversal (i.e. from head as well as tail) in alternate fashion, so that (used) block congestion doesn't occur at the start of the block list.
4. Implemented deferred coalescing so that searching and coalescing happens simultaneously and space utilisation is improved.
5. In realloc part, added next free block coalescing function. If the adjacent block is free, then some portion of it gets assigned and other half gets fragmented. Hence space as well as throughput is improved.

The reason for our design being optimal for widest variety of workloads is:
	1. We are using a modified first first statergy in which the traversal occurs in both the direction (i.e. from start to tail and vice versa) after every request.
	   Because of this there is no congestion of used blocks at one end and hence it's distributed across the list.
	2. The malloc request has buffer depending on the request inorder improve the throughput of realloc. 
	3. Also deffered coalescing technique (coalescing while searching for the block) helps optimise the space simulataneously. Hence space utilisation is improved.
	4. Performing periodic coalescing throughout the list (after particular number of free requests) helps maintain the blocks in defragmented state. 
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
	unsigned long int curr_size, actual_size;
} Header;



Header *free_list_start, *free_list_end;

// list traversal flag
int fwd_traversal=0;
int coalesce_flag=0;
int coalesce_counter=0, coalesce_max=15;  //20
int p_counter=0, p_max=0; // number of printf's




int mm_init(void)
{
	fwd_traversal=1;
	coalesce_flag=0;
	coalesce_counter=0;
	free_list_start=NULL;
	free_list_end=NULL;
    return 0;		//Returns 0 on successfull initialization.
}



int is_free(unsigned long int n)
{
    return (((n ^ 1) & 1) ^ 1);
}


// Modified First fit 
Header *search_free_list(size_t size)
{
	Header *curr;

	fwd_traversal=!fwd_traversal;

	if(fwd_traversal)
		curr = free_list_start;
	else
		curr = free_list_end;

	while(curr) {

		if (!coalesce_flag && is_free(curr->actual_size) && (curr->actual_size ^ 1) >= size )
		{
			return curr;
		}

		// Deferred coalesce Technique
		if(is_free(curr->actual_size) && curr->next && is_free(curr->next->actual_size))
		{
			curr->actual_size= (((curr->actual_size ^1) + (curr->next->actual_size ^ 1) + sizeof(Header)) ^ 1);
			
			if(curr->next->next)
			{
				curr->next->next->prev=curr;
				curr->next=curr->next->next;
			}
			else
			{
				free_list_end=curr;
				curr->next=NULL;
			}
		}
		else
		{
			if(fwd_traversal)
				curr = curr->next;
			else
				curr = curr->prev;
		}

	}
	if(coalesce_flag)
		coalesce_flag=0;

	return NULL;
}





void *mm_malloc(size_t size)
{
	if(size <= 0){		// Invalid request size
		return NULL;
	}

	size = ALIGN(size);


	//traversing through the list of blocks to see if any block is present with required size (first fit)
	Header *header = (Header *) search_free_list(size);

	unsigned long int buffer=0;  //0

	if(size>=1024)
		buffer=32;


	if(header==NULL)
	{
		//if no block is present, request for new block
		unsigned long int total_size = size + buffer;
		header = mem_sbrk(sizeof(Header)+total_size);
		header->curr_size=size;
		header->actual_size=total_size;
		header->next = NULL;
		
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

	header->actual_size= (header->actual_size ^ 1);

	//fragment the chunk to desired size before returning pointer
	if(header->actual_size > size+buffer+sizeof(Header)+ALIGNMENT)
	{
		
		unsigned long int total = sizeof(Header) + size + buffer;
		unsigned long int remaining_size=header->actual_size - total;
		header->actual_size=size+buffer;
		header->curr_size=size;

		Header *new_fragmented_block= (void *)header + total;
		new_fragmented_block->actual_size=(remaining_size ^ 1); // XOR with 1 indicates free block
		new_fragmented_block->curr_size=8;
		new_fragmented_block->next=header->next;
		if(new_fragmented_block->next)
			new_fragmented_block->next->prev=new_fragmented_block;
		else
			free_list_end=new_fragmented_block;
		
		header->next=new_fragmented_block;
		new_fragmented_block->prev=header;	
	}
	else
	{
		header->curr_size=size;
	}
	
	return (void *)(header+1);
}




void mm_free(void *ptr)
{
	if (ptr==NULL)
		return;

	Header *header=(Header *)ptr - 1;
	header->actual_size = (header->actual_size ^ 1);

	coalesce_counter++;
	if(coalesce_counter>=coalesce_max)
	{
		coalesce_counter=0;
		coalesce_flag=1;

		search_free_list(0);

	}
}


/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
	
	if(ptr == NULL){			//memory was not previously allocated
		return mm_malloc(size);
	}
	
	if(size == 0){				//new size is zero
		mm_free(ptr);
		return NULL;
	}


	Header *header = (Header *)ptr-1;
	unsigned long int ptr_curr_size=header->curr_size ;
	unsigned long int ptr_actual_size=header->actual_size ;

	
	if(ptr_curr_size == size)
		return ptr;

	if((size < ptr_curr_size) || (size > ptr_curr_size && size <= ptr_actual_size))
	{
		header->curr_size=size;
		return ptr;
	}

	unsigned long int aligned_size= ALIGN(size);
	unsigned long int extra_size = aligned_size - header->actual_size;

	// Check if forward block is free. If yes then perform forward coaleesce and return
	if(header->next && is_free(header->next->actual_size) && (header->next->actual_size ^ 1) >= extra_size)
	{
		unsigned long int buffer=0;

		if(size>=1024 && size<2048)
			buffer=64;
		else if(size>=2048 && size<4096)
			buffer=128;
		else if(size>=4096 && size<16384)
			buffer=512;
		else
			buffer=2048;


		if((header->next->actual_size ^ 1) > extra_size + buffer + sizeof(Header)+ ALIGNMENT)
		{
			
			unsigned long int total = sizeof(Header) + aligned_size + buffer;
			unsigned long int remaining_size=(header->next->actual_size ^ 1) - extra_size -buffer;
			header->actual_size=aligned_size+buffer;
			header->curr_size=size;

			Header *next_header=header->next;

			Header *new_fragmented_block= (void *)header + total;
			new_fragmented_block->actual_size=(remaining_size ^ 1); // XOR with 1 indicates free block
			new_fragmented_block->curr_size=8;
			new_fragmented_block->next=next_header->next;
			
			if(new_fragmented_block->next)
				new_fragmented_block->next->prev=new_fragmented_block;
			else
				free_list_end=new_fragmented_block;
			
			header->next=new_fragmented_block;
			new_fragmented_block->prev=header;

		}
		else
		{
			header->actual_size+= ((header->next->actual_size ^ 1) + sizeof(Header));
			header->curr_size=size;
			
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
		
		return ptr;

	}


	void *new_ptr = mm_malloc(size);
	memcpy(new_ptr, ptr, ptr_curr_size);

	mm_free(ptr);

	return new_ptr;
	
}

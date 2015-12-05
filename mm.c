#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

extern mem_ptr Heap;

mem_ptr mm_malloc(int size) {
   /* Input: size of the block needed. You can assume size > 0
      Output:
		- Return a pointer to a mem_rec of the appropriate size (new_size).
		- This block should be found using first-fit.
		- If there is nowhere to place a block of the given size, print:
			ERROR: Insufficient heap space for desired allocation
		  and return a NULL pointer.
   */
  int new_size = ALIGN(size);
  //Check if the size asked for isn't too large and that the heap is free.
  //This is the special case when no memory has been allocated yet and the heap is one big block.
  int allocated = GET_ALLOC(Heap -> status);
  if(new_size <= GET_SIZE(Heap -> status) && !GET_ALLOC(Heap -> status))
  {
  	//Create new memory block with total size of (heap - size of item taking up the heap)
  	mem_ptr newBlock = (mem_ptr)malloc(sizeof(mem_rec));
  	(newBlock -> status) = PACK(GET_SIZE(Heap -> status) - new_size, 0);
  	//Run initializations for the new block, set it to be a free node that points back to the Heap and forwards to nothing
  	newBlock -> previous = Heap;

  	if(Heap -> next)
  	{
  		newBlock -> next = Heap -> next;
  		Heap -> next -> previous = newBlock;
  	}
  	else
  	{
  		newBlock -> next = NULL;
  	}
  	//Connect the linked list from the Heap's end, here "Heap" will refer to the first block of the memory linked list.
  	//Set Heap to being not free and give the new block the memory address it needs.
  	Heap -> next = newBlock;
  	newBlock -> address = new_size;
  	Heap -> status = PACK(new_size, 1);
  	allocated = GET_ALLOC(Heap -> status);
  	cleanUp(Heap);
  	return Heap;
  }
  //If either we cannot fit into the heap or the first block of the LL is taken, come down here and let's traverse.
  else
  {
  	mem_ptr temp = Heap;
  	while((temp -> next != NULL))
  	{
  		temp = temp -> next;
  		allocated = GET_ALLOC(temp -> status);
  		if(new_size <= GET_SIZE(temp -> status) && (GET_ALLOC(temp -> status) == 0))
  		{
  			//Create new memory block with total size of (temp - size of item taking up the heap)
  			mem_ptr newBlock = (mem_ptr)malloc(sizeof(mem_rec));
	  		(newBlock -> status) = PACK(GET_SIZE(temp -> status) - new_size,0);
		  	//Run initializations for the new block, set it to be a free node that points back to the temp and forwards to nothing
		  	mem_ptr tempBlock = temp;
		  	newBlock -> previous = tempBlock;		  	
		  	if(temp -> next)
		  	{
		  		newBlock -> next = temp -> next;
		  		temp -> next -> previous = newBlock;
		  	}
		  	else
		  	{
		  		newBlock -> next = NULL;
		  	}
		  	//Connect the linked list from the temp's end
		  	//Set temp to being not free and give the new block the memory address it needs.
		  	temp -> next = newBlock;
		  	newBlock -> address = GET_SIZE(temp -> address) + new_size;
		  	temp -> status = PACK(new_size, 1);
		  	cleanUp(Heap);
		  	return temp;
  		}
  	}
  }
  printf("ERROR: Insufficient heap space for desired allocation\n");
  return NULL;
}

void mm_free(mem_ptr m) {
   /*  Input: pointer to a mem_rec
       Output:  None
		- You need to be sure that after the call, the status of the given
		  block is FREE.
		- You must coalesce this block with adjacent blocks if appropriate.
         - If the input pointer is null, print:
			ERROR: Cannot free empty node
         - If the input pointer points to an already free node, print:
			ERROR: Node already free
		  and return.
    */
	//If Null, tell caller we are done
	if (m == NULL)
	{
		printf("ERROR: Cannot free empty node\n");
		return;
	}
	else
	{
		//Can't free what is already free...or can you? No, no you can't.
		if(!GET_ALLOC(m -> status))
		{
			printf("ERROR: Node already free\n");
			return;
		}
		else
		{
			//If node is not null and not already free, then set it to be free
			m -> status = PACK(GET_SIZE(m -> status), 0);
			//Coalesce if need be.
			coalesce(m);
			//Check to ensure all the blocks are freed after coalescing.
			cleanUp(Heap);
		}
	}
}

mem_ptr mm_realloc(mem_ptr m, int size) {
   /* Input: pointer to a mem_rec, new size of the block needed
      Output:
		- If the input pointer is null, print:
         		ERROR: Cannot free empty node
           and return.
		- Return a pointer to a mem_rec of the appropriate size (new_size).
		- This block should be chosen as follows:
		  - if the new size is less than the current size of the block, use 
		    the current block after moving the excess back to the free list 
		  - if the new block size is larger than the current size, first see 
		    if there is enough space after the current block to expand.
		  - If this will not work, you will need to free the current block
		    and find a first-fit (from the start of memory) location for 
		    this larger block.
		  - If there is nowhere to place a block of the given size, print:
			ERROR: Insufficient heap space for desired allocation
		    and return a NULL pointer.
   */
   int new_size = ALIGN(size);
   //Check the node is not null
   if(!m)
   {
   	printf("ERROR: Cannot free empty node\n");
   	return;
   }
   if(new_size == GET_SIZE(m->status))
   {
   	return m;
   }
   //Check if the new block's size is smaller than the current block
   if(new_size < GET_SIZE(m -> status))
   {
   	//If so, start the process of splitting the block into two.
   	//Put the current size into a temp var, this will be used to create the new block
   	int tempVal = GET_SIZE(m->status);
   	//Change the size of the current block to the new size coming in
   	m -> status = PACK(new_size,1);
   	//Put the next of the linked list into a temp node.
   	//This will be used to reconnect the linked list to the new node.
   	mem_ptr temp = m -> next;
   	//Break the linked list by having m point to a new mem_ptr.
   	m -> next = (mem_ptr)malloc(sizeof(mem_rec));
   	//Make sure it's doubly linked.
   	m -> next -> previous = m;
   	//Give the new block size of previous block size - new size
   	m-> next -> status = PACK(tempVal-new_size,0);
   	//Update the address of the new node.
   	m -> next -> address = (m -> address + GET_SIZE(m->status));
   	//Check if the temp node is not null. If not, connect the rest of the LL back
   	if(temp)
   	{
   		m -> next -> next = temp;
   		temp -> previous = m-> next;
   	}
   	//return the new node.
   	coalesce(m -> next);
   	cleanUp(Heap);
   	return m;
   }
   //if new_size > current size, let's figure out what to do
   else
   {
   	//Two checks here are necessary, if m has no next node, then there is nothing to add to.
   	//If m has a next node and it is still too small compared to new_size.
   	if(!(m->next) || (new_size > (GET_SIZE(m->status) + GET_SIZE(m->next -> status))) || GET_ALLOC(m-> next->status))
   	{
   		//Here we just use mm_free and mm_malloc, as these functions already deal with general adding and deleting of memory.
   		mm_free(m);
   		return mm_malloc(size);
   	}
   	else
   	{
   		//Keep track of the difference between the new size and the original size.
   		//This will be used for modifying the next node over, to simulate taking parts of it.
   		int difference = new_size - GET_SIZE(m->status);
   		//Reduce the size of the next block
   		m -> next -> status -= (difference);
   		//Change the size of the current block to the new size.
   		m -> status = PACK(new_size,1);
   		//Push the next block further away.
   		m -> next -> address += (difference);
   		//Finally check, maybe we used up all the space allotted for the next block and it must be removed.
   		cleanUp(Heap);
   		return m;
   	}
   }
   return NULL;

}
//This function will be called to free up empty blocks, rather than do it manually whenever need be.
void cleanUp(mem_ptr m)
{
	//Go through the heap and clean up the memory, namely remove all elements of size 0
	while(m)
	{
		//If we found a node of size 0, then go perform clean up on it.
		if(!(m -> status))
		{
			//Rearrange the links on the LL to skip over the
			m -> previous->next = m->next;
			if(m -> next)
			{
				m -> next -> previous = m -> previous;
			}
			free(m);
		}
		m = m->next;
	}
}
//Function to coalesce two or more free blocks.
void coalesce(mem_ptr m)
{
	if(m -> previous != NULL && !GET_ALLOC(m -> previous -> status))
	{
		//Increase the size of the previous block by the size of the current block being freed.
		(m -> previous -> status) += GET_SIZE(m -> status);
		//Check if the next block is also free. 
		if(m -> next != NULL && !GET_ALLOC(m -> next -> status))
		{
			//If so, then add to the block before the one being freed again.
			(m -> previous -> status) += GET_SIZE(m->next ->status);
			//Check to see if there is block two blocks away
			m -> previous -> next = m -> next -> next;
			if(m -> next -> next != NULL)
			{
				//Connect that block to the block before the freed block.
				//If we were (1 -> 2 -> 3 -> 4), with 1, 3 free.
				//Now we are (1 -> 4), with 
				m -> next -> next -> previous = m -> previous;
			}
			if(m->next)
			{
				free(m->next);
			}
		}
		//If the next block is free, then we will need to connect it to the block before the one needing freeing.
		else
		{
			//Connect the blocks. Note that m -> previous is allowed to point to null afterwards.
			//If we were 1 -> 2 -> 3, with 1 free. (situation 2)
			//We are now 1 -> 3, with 1 free.
			m -> previous -> next = m -> next;
			if(m -> next != NULL)
			{
				m -> next -> previous = m -> previous;
			}
		}
		if(m)
		{
			free(m);
		}
		cleanUp(Heap);
		return;
	}
	//Now check the situation where the next block is free, but not the previous block.
	if(m -> next != NULL && !GET_ALLOC(m -> next -> status))
	{
		//Here the next block will merge with the current block
		(m -> status) += GET_SIZE(m -> next -> status);
		//Set the next block to have size zero
		m -> next -> status = 0;
		//Perform memory management
		cleanUp(Heap);
		return;
	}
}
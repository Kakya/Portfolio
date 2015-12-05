#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

#define MAX_INDEX 10000
#define DEBUG 1

mem_ptr Heap = NULL;

static mem_ptr allocs[MAX_INDEX];
extern mem_ptr mm_malloc(int),mm_realloc(mem_ptr,int);
extern void mm_free(mem_ptr),mm_dump(); 

main(int argc, char**argv) {
    FILE *f;
    int num,i;
    if (argc != 2) {
      printf("Usage: %s trace_file\n",argv[0]);
    }
    if (f = fopen(argv[1],"r"))  {
      int op; int index, size;
      init_driver();
      mm_init();
      while (fscanf(f,"%d %d %d",&op,&index,&size)) {
         if (op == 1) { allocs[index] = mm_malloc(size);}
         else if (op == 2) {mm_free(allocs[index]);allocs[index]=NULL;}
	 else if (op == 3) {allocs[index] = mm_realloc(allocs[index],size); }
         else if (op == 4)  {mm_dump();}
         else if (op == 0) exit(1);
      }
    } else printf("Unknown trace file\n");

}


init_driver() {
   int i;
   for (i=0;i<MAX_INDEX;i++) 
        allocs[i] = NULL;
}




mm_init() {
   Heap = (mem_ptr)malloc(sizeof(mem_rec));
   Heap->status = PACK(ALIGN(HEAPSIZE),FREE);
   Heap->address = 0;
   Heap->previous = Heap->next = NULL;
}

void mm_dump() {
   mem_ptr t = Heap;
   printf("Memory Contents: \n");
   while(t) {
     printf("%5d: size = %-5d status = ",t->address,GET_SIZE(t->status));
     if (GET_ALLOC(t->status) == 0) printf("free\n"); 
     else printf("allocated\n");
     t = t->next;
   }
   printf("\n");
}


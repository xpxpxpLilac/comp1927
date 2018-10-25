//gcc -Wall -Werror -O -o testAllocator testAllocator.c allocator.h
//A simple unit test for allocator.c
//let me know if there are bugs or mistakes

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "allocator.h"
#include "allocator.c"

#define FALSE 0
#define TRUE 1

void unitTest(void);
void printLine(void);


int main(int argc, char *argv[]) {
   unitTest();
   fprintf(stderr, "\nAll tests passed! You are awesome!\n\n");

   return EXIT_SUCCESS;
}


void unitTest(void) {
   fprintf(stderr, "\n---------- > Unit Test < ----------\n\n");
   fprintf(stderr, "Testing vlad_init(2013) ......\n");
   assert(memory == NULL);
   vlad_init(2013); //DONT CHANGE 
   assert(memory != NULL);
   assert(memory_size == 2048);
   assert(free_list_ptr == 0);
   assert(strategy == BEST_FIT);
   
   free_header_t *freeRegion = (free_header_t *) &memory[free_list_ptr]; 
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size == memory_size);
   assert(freeRegion->prev == 0);
   assert(freeRegion->prev == 0);
   
   fprintf(stderr, "> memory = %p\n", memory);
   fprintf(stderr, "> memory_size = %d\n", memory_size);
   fprintf(stderr, "> free_list_ptr = %d\n", free_list_ptr);
   fprintf(stderr, "> strategy = BEST_FIT (%d)\n\n", BEST_FIT);

   vlad_stats();
   fprintf(stderr, "passed!\n");
   printLine();

   fprintf(stderr, "Testing vlad_malloc() ......\n");
   fprintf(stderr, "> ptr1: vlad_malloc(3)\n");
printf("head of list is %d\n",free_list_ptr);

   byte *ptr1 = vlad_malloc(3);
   assert(ptr1 != NULL);
   alloc_header_t *allocRegion = (alloc_header_t *) &memory[0];
   assert(allocRegion != NULL); 
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 16);
   freeRegion = (free_header_t *) &memory[16];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size = memory_size - 16);
   assert(freeRegion->prev == 16);
   assert(freeRegion->next == 16);
   assert(free_list_ptr == 16);
printf("head of list is %d\n",free_list_ptr);
printf("ptr1 is %d\n",ptr1-memory);
   fprintf(stderr, "> ptr2: vlad_malloc(20)\n");
   byte *ptr2 = vlad_malloc(20);
   assert(ptr2 != NULL);

   assert(allocRegion != NULL); 
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 16);

   allocRegion = (alloc_header_t *) &memory[16];
   assert(allocRegion != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 28);
  
   freeRegion = (free_header_t *) &memory[44];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size == memory_size - 16 - 28); 
   assert(freeRegion->prev == 44);
   assert(freeRegion->next == 44);
   assert(free_list_ptr == 44);

printf("head of list is %d\n",free_list_ptr);

   fprintf(stderr, "> ptr3: vlad_malloc(30)\n");
   byte *ptr3 = vlad_malloc(30);
   assert(ptr3 != NULL);
   allocRegion = (alloc_header_t *) &memory[44];
   assert(allocRegion != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 40);

   freeRegion = (free_header_t *) &memory[84];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size = memory_size - 16 - 28 - 40);
   assert(freeRegion->prev == 84);
   assert(freeRegion->next == 84);
   assert(free_list_ptr == 84);

printf("head of list is %d\n",free_list_ptr);

   fprintf(stderr, "> ptr4: vlad_malloc(40)\n");
   byte *ptr4 = vlad_malloc(40);
   assert(ptr4 != NULL);
   allocRegion = (alloc_header_t *) &memory[84];
   assert(allocRegion != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 48);

   freeRegion = (free_header_t *) &memory[132];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size = memory_size - 16 - 28 - 40 - 48);
   assert(freeRegion->prev == 132);
   assert(freeRegion->next == 132);
   assert(free_list_ptr == 132);

printf("head of list is %d\n",free_list_ptr);

   fprintf(stderr, "> ptr5: vlad_malloc(50)\n");
   byte *ptr5 = vlad_malloc(50);
   assert(ptr5 != NULL);
   allocRegion = (alloc_header_t *) &memory[132];
   assert(allocRegion != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 60);

   freeRegion = (free_header_t *) &memory[192];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size = memory_size - 16 - 28 - 40 - 48 - 60);
   assert(freeRegion->prev == 192);
   assert(freeRegion->next == 192);
   assert(free_list_ptr == 192);

printf("head of list is %d\n",free_list_ptr);

   fprintf(stderr, "> ptr6: vlad_malloc(60)\n");
   byte *ptr6 = vlad_malloc(60);
   assert(ptr6 != NULL);
   allocRegion = (alloc_header_t *) &memory[192];
   assert(allocRegion != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 68);

   freeRegion = (free_header_t *) &memory[260];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size = memory_size - 16 - 28 - 40 - 48 - 60 - 68);
   assert(freeRegion->prev == 260);
   assert(freeRegion->next == 260);
   assert(free_list_ptr == 260);

printf("head of list is %d\n",free_list_ptr);
printf("freeregion magic is %x\n",freeRegion->magic);

   fprintf(stderr, "> ptr7: vlad_malloc(2000) --> Oversized --> NULL pointer \n");
   byte *ptr7 = vlad_malloc(2000);
   assert(ptr7 == NULL);
printf("freeregion magic is %x\n",freeRegion->magic);

   vlad_stats();
   fprintf(stderr, "passed!\n");
   printLine();
printf("head of list is %d\n",free_list_ptr);

   fprintf(stderr, "Testing vlad_free() & vlad_merge()\n");   
   fprintf(stderr, "> 1. vlad_free(ptr5)\n");
printf("freeregion magic is %x\n",freeRegion->magic);

   vlad_free(ptr5);
printf("index is %d\n",ptr1-memory);
printf("index is %d\n",ptr2-memory);
printf("index is %d\n",ptr3-memory);
printf("index is %d\n",ptr4-memory);
printf("index is %d\n",ptr5-memory);
printf("index is %d\n",ptr6-memory);
printf("freeregion magic is %x\n",freeRegion->magic);
printf("head of list is %d\n",free_list_ptr);
   assert(free_list_ptr == 132);
   free_header_t *freeRegion3 = (free_header_t *) &memory[132];
   assert(freeRegion3 != NULL);
   assert(freeRegion3->magic == MAGIC_FREE);
   assert(freeRegion3->size == 60);
   assert(freeRegion3->prev = 260);
   assert(freeRegion3->next == 260);   
   free_header_t *freeRegion4 = freeRegion;
   assert(freeRegion4 != NULL);
   assert(freeRegion4->magic == MAGIC_FREE);
   assert(freeRegion4->size == 1788);
   assert(freeRegion4->prev = 132);
   assert(freeRegion4->next == 132);

   fprintf(stderr, "> 2. vlad_free(ptr1)\n");
   vlad_free(ptr1);
   assert(free_list_ptr == 0);
   free_header_t *freeRegion1 = (free_header_t *) &memory[0];
   assert(freeRegion1 != NULL);
   assert(freeRegion1->magic == MAGIC_FREE);
   assert(freeRegion1->size == 16);
   assert(freeRegion1->prev = 260);
   assert(freeRegion1->next == 132);   
   assert(freeRegion3 != NULL);
   assert(freeRegion3->magic == MAGIC_FREE);
   assert(freeRegion3->size == 60);
   assert(freeRegion3->prev == 0);
   assert(freeRegion3->next == 260);    
   assert(freeRegion4 != NULL);
   assert(freeRegion4->magic == MAGIC_FREE);
   assert(freeRegion4->size == 1788);
   assert(freeRegion4->prev = 132);
   assert(freeRegion4->next == 0);

   fprintf(stderr, "> 3. vlad_free(ptr3)\n");
   vlad_free(ptr3);
   assert(free_list_ptr == 0);
   free_header_t *freeRegion2 = (free_header_t *) &memory[44];
   assert(freeRegion2 != NULL);
   assert(freeRegion2->magic == MAGIC_FREE);
   assert(freeRegion2->size == 40);
   assert(freeRegion2->prev == 0);
   assert(freeRegion2->next == 132);
   assert(freeRegion1 != NULL);
   assert(freeRegion1->magic == MAGIC_FREE);
   assert(freeRegion1->size == 16);
   assert(freeRegion1->prev = 260);
   assert(freeRegion1->next == 44);   
   assert(freeRegion3 != NULL);
   assert(freeRegion3->magic == MAGIC_FREE);
   assert(freeRegion3->size == 60);
   assert(freeRegion3->prev == 44);
   assert(freeRegion3->next == 260);    
   assert(freeRegion4 != NULL);
   assert(freeRegion4->magic == MAGIC_FREE);
   assert(freeRegion4->size == 1788);
   assert(freeRegion4->prev = 132);
   assert(freeRegion4->next == 0);
   vlad_stats();

printf("freelist head is %d\n",free_list_ptr);

   fprintf(stderr, "> 4. vlad_free(ptr2) --> vlad_merge()\n");
   vlad_free(ptr2);
   assert(free_list_ptr == 0);
   assert(freeRegion1 != NULL);
   assert(freeRegion1->magic == MAGIC_FREE);
   assert(freeRegion1->size == 16 + 28 + 40);
   assert(freeRegion1->prev == 260);
   assert(freeRegion1->next == 132);
   assert(freeRegion3 != NULL);
   assert(freeRegion3->magic = MAGIC_FREE);
printf("freeregion3 prev is %d\n",freeRegion3->prev);
printf("freeregion2 prev is %d\n",freeRegion2->prev);
printf("freeregion1 next is %d\n",freeRegion1->next);

   assert(freeRegion3->size == 60);
   assert(freeRegion3->prev == 0);
   assert(freeRegion3->next == 260);
   assert(freeRegion4->magic == MAGIC_FREE);
   assert(freeRegion4->size == 1788);
   assert(freeRegion4->prev = 132);
   assert(freeRegion4->next == 0); 
   vlad_stats();
   fprintf(stderr, "passed!\n");
   printLine();   


   fprintf(stderr, "More tests ......\n");
printf("head of list is %d\n",free_list_ptr);
   fprintf(stderr, "> 1. ptr1 = vlad_malloc(76)\n");
   ptr1 = vlad_malloc(76);
   assert(ptr1 != NULL);
   assert(free_list_ptr == 132);
   allocRegion = (alloc_header_t *) &memory[0];
   freeRegion1 = (free_header_t *) &memory[132];
   freeRegion2 = (free_header_t *) &memory[260];
   assert(allocRegion != NULL);
   assert(freeRegion1 != NULL);
   assert(freeRegion2 != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 84);
   assert(freeRegion1->magic == MAGIC_FREE);
   assert(freeRegion1->size == 60);
   assert(freeRegion1->prev == 260);
   assert(freeRegion1->next == 260);
   assert(freeRegion2->magic == MAGIC_FREE);
   assert(freeRegion2->size == 1788);
   assert(freeRegion2->prev == 132);
   assert(freeRegion2->next == 132);
   
   
   fprintf(stderr, "> 2. ptr2 = vlad_malloc(1780)\n");
printf("head of list is %d\n",free_list_ptr);
   ptr2 = vlad_malloc(1780);
printf("head of list is %d\n",free_list_ptr);
   assert(ptr2 != NULL);
   assert(free_list_ptr == 132);
   allocRegion = (alloc_header_t *) &memory[260];
   freeRegion1 = (free_header_t *) &memory[132];
   assert(freeRegion1 != NULL);
   assert(allocRegion != NULL);
   assert(freeRegion1->magic == MAGIC_FREE);
   assert(freeRegion1->size == 60);
   assert(freeRegion1->prev == 132);
   assert(freeRegion1->next == 132);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 1788);   
   vlad_stats();

   fprintf(stderr, "> 3. ptr7 = vlad_malloc(20)\n");

printf("head of list is %d\n",free_list_ptr);
free_header_t *curr =(free_header_t *)&memory[free_list_ptr];
printf("curr size is %d\n",curr->size);

  
   ptr7 = vlad_malloc(20);
printf("head of list is %d\n",free_list_ptr);
printf("head of list is %d\n",free_list_ptr);

   assert(ptr7 != NULL);
   assert(free_list_ptr == 160);
   allocRegion = (alloc_header_t *) &memory[132];
   assert(allocRegion != NULL);
   assert(allocRegion->magic == MAGIC_ALLOC);
   assert(allocRegion->size == 28);
   freeRegion = (free_header_t *) &memory[160];
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
   assert(freeRegion->size == 32);
   assert(freeRegion->prev == 160);
   assert(freeRegion->next == 160);
   vlad_stats();
   fprintf(stderr, "passed!\n");
   printLine();
/*
   fprintf(stderr, "> 4. vlad_free(*all ptrs) --> vlad_merge() --> 1 free Region\n");
 //  vlad_free(ptr7);
   vlad_free(ptr6); 
   vlad_free(ptr4);
//   vlad_free(ptr2);
   vlad_free(ptr1);
   freeRegion = (free_header_t *) &memory[0];
   assert(free_list_ptr == 0);
   assert(freeRegion != NULL);
   assert(freeRegion->magic == MAGIC_FREE);
//   assert(freeRegion->size == 2048);
   assert(freeRegion->prev == 0);
   assert(freeRegion->next == 0);
   vlad_stats();
   fprintf(stderr, "passed!\n");
   printLine();
*/
   fprintf(stderr, "Final Test: vlad_end()\n");
   vlad_end();
   assert(memory == NULL);
   fprintf(stderr, "passed!\n");
   printLine();
}

void printLine(void) {
   fprintf(stderr, "------------------------------------------\n\n");
}

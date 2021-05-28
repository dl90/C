#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define KB 1024
#define randNum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

void printAddrs(char *, int len);
void randChar(char *, int len);

/*
  # dynamic memory allocation

  we may not know the exact memory needs to run the program
  memory allocation will be needed during the run time

  C does not have automatic garbage collection
  so we need to manage all dynamic memory used during execution

  variable declarations (int x) uses the stack
  dynamic variables (malloc) uses the heap
*/

int main() {

  char *mem_1, *mem_2;
  unsigned int mem_1_len, mem_2_len;

  /*
    malloc (memory allocation)

    allocates a block of memory of specified bytes
    does not initialize or clear existing data in memory block
    type is needed to calc size of allocation and pointer traversal

    if success returns a pointer to the first address of the memory
    if allocation fails (insufficent memory) the call returns a NULL pointer
  */
  mem_1_len = KB / 16;
  mem_1 = (char *)malloc(sizeof(char) * mem_1_len);

  if (mem_1 == NULL) {
    printf("mem_1 memory error\n");
    return 1;
  }
  printf("%p, %d\n", mem_1, mem_1_len);
  randChar(mem_1, mem_1_len);
  // printAddrs(mem_1, mem_1_len);

  /*
    calloc (contiguous allocation)

    allocates contiguous memory of specified count and size and initialize all bits to zero
  */
  mem_2_len = 10;
  mem_2 = (char *)calloc(mem_2_len, sizeof(char));

  if (mem_2 == NULL) {
    printf("mem_2 memory error\n");
    return 1;
  }
  printf("%p, %d\n", mem_2, mem_2_len);
  randChar(mem_2, mem_2_len);
  // printAddrs(mem_2, mem_2_len);

  /*
    realloc

    change the size of previously allocated memory
    if pointer is NULL, call is same as malloc
    if size is 0, call is same as free
  */
  mem_1_len = KB / 8;
  mem_1 = (char *)realloc(mem_1, sizeof(char) * mem_1_len);

  if (mem_1 == NULL) {
    printf("mem_1 memory error\n");
    return 1;
  }
  printf("%p, %d\n", mem_1, mem_1_len);
  randChar(mem_1, mem_1_len);
  // printAddrs(mem_1, mem_1_len);

  /*
    releases memory allocated after use
    calling twice results in double free memory error

    memory leaks

    memory allocated but not released propertly after it is no longer needed
    eg: losing reference to allocated memory block
    DO NOT MODIFY ORIGINAL REFERENCE returned by memory allocation calls, assign another pointer
  */
  // free(mem_1);
  free(mem_2);

  printAddrs(mem_1, mem_1_len);
  printAddrs(mem_2, mem_2_len);

  // assign NULL to freed pointers to prevent future accidental assignments
  // mem_1 = NULL;
  mem_2 = NULL;

  /*
    memcpy

    copies n bytes from a src to a dest, returns pointer to dest
    memory areas of src and dest should not overlap
  */
  mem_2 = (char *)malloc(sizeof(char) * mem_1_len);
  mem_2 = memcpy(mem_2, mem_1, mem_1_len);
  printAddrs(mem_1, mem_1_len);
  printAddrs(mem_2, mem_1_len);

  /*
    memmove

    similar to memcpy but allows overlap
  */
  char nums[10] = {'a', 'b', 'c', 'd', 'e'};
  char *ptr;

  ptr = memmove(nums + 3, nums, 7);
  printAddrs(nums, 10);
  printAddrs(ptr, 6);

  free(mem_1);
  free(mem_2);

  return 0;
}

void printAddrs(char *ptr, int len) {
  for (int i = 0; i < len; i++) {
    printf("%p => %c\t", ptr + i, *(ptr + i));
    if (i && (i + 1) % 5 == 0)
      printf("\n");
  }
  printf("\n%s\n\n", ptr);
}

void randChar(char *ptr, int len) {
  srand((unsigned)time(0));

  for (int i = 0; i < len; i++)
    *(ptr + i) = randNum(33, 126);
}

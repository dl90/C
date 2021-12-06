#include <stdio.h>
#include <stdlib.h> // qsort

int add_i(int a, int b);
int sub_i(int a, int b);
int mul_i(int a, int b);
int div_i(int a, int b);
int mod_i(int a, int b);

void printArr(int *arr, int len);
int ascendCompare(const void *l, const void *r);
int descendCompare(const void *l, const void *r);

int main(void) {

  int (*funcPtr)(int, int);       // defines a function pointer
  int (*arrFuncPtr[5])(int, int); // defines an array of function pointers.

  int a = 2;
  int b = 3;
  int opSelector = 0;

  // assign function to function pointer (must be same type)
  funcPtr = add_i;

  arrFuncPtr[0] = add_i;
  arrFuncPtr[1] = sub_i;
  arrFuncPtr[2] = mul_i;
  arrFuncPtr[3] = div_i;
  arrFuncPtr[4] = mod_i;

  // preferred due to explicit dereference, not confused with function call
  printf("%d\n", (*funcPtr)(a, b));
  printf("%d\n", funcPtr(a, b));
  printf("%d\n", arrFuncPtr[opSelector](a, b));
  puts("");

  int numbers[] = {5, 9, 2, 25, 3, 18, 1, 22};
  int arraySize = sizeof(numbers) / sizeof(int);
  int (*orderFuncPtr[2])(const void *, const void *) = {ascendCompare, descendCompare};

  qsort(numbers, arraySize, sizeof(int), orderFuncPtr[0]);
  printArr(numbers, arraySize);
  qsort(numbers, arraySize, sizeof(int), orderFuncPtr[1]);
  printArr(numbers, arraySize);
}

int add_i(int a, int b) { return a + b; }
int sub_i(int a, int b) { return a - b; }
int mul_i(int a, int b) { return a * b; }
int div_i(int a, int b) { return a / b; }
int mod_i(int a, int b) { return a % b; }

void printArr(int *arr, int len) {
  for (int i = 0; i < len; ++i)
    printf("%d ", arr[i]);

  puts("");
}

int ascendCompare(const void *l, const void *r) {
  int result = 0;
  int *L = (int *)l;
  int *R = (int *)r;

  if (*L > *R)
    result = 1;
  else if (*L < *R)
    result = -1;

  return result;
}

int descendCompare(const void *l, const void *r) {
  return *(int *)r - *(int *)l;
}

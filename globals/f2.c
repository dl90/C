#include <stdio.h>

// static scopes this global to this file
static int GLOBAL_VARIABLE = -1;

void func2() {
  printf("func2: %d\n", GLOBAL_VARIABLE);
}
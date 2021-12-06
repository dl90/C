#include <stdio.h>

// extern is required as the global is only declared and will be linked to definition in main
extern int GLOBAL_VAR;

void func1() {
  printf("func1: %d\n", GLOBAL_VAR);
  GLOBAL_VAR += 1;
}

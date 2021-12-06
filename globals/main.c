#include <stdio.h>

// gcc main.c f1.c f2.c
// extern is optional as the global is defined here
int GLOBAL_VAR = 10;

void func1();
void func2();

int main(void) {

  printf("main: %d\n", GLOBAL_VAR);
  func1();

  // GLOBAL_VAR updated by f1
  printf("main: %d\n", GLOBAL_VAR);

  func2();
  printf("main: %d\n", GLOBAL_VAR);
}
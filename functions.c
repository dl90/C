#include <stdio.h>

const int STR_SIZE = 256;

void hi(void);
void parse(char *);
void upper(char *);
double pow2(int n, int p);

/*
  parameters are passed by value (copies) and does not modify the argument passed
  passing by pointer will modify the argument

  Note:
    theres no default values for functions in C
    function variables are local and is destroyed after call
    functions can not access variables outside its scope, only values passed
*/

int main(void) {
  char str[STR_SIZE];
  double num;
  int x, y;

  hi();
  parse(str);
  upper(str);

  printf("enter 2 nums (pow): ");
  scanf("%d", &x);
  scanf("%d", &y);
  num = pow2(x, y);

  printf("\n%s", str);
  printf("%f\n\n", num);

  return 0;
}

void hi() {
  printf("\nHello, World!\n");
}

void parse(char *str) {
  printf("enter string: ");
  fgets(str, STR_SIZE, stdin);
}

void upper(char *str) {
  char *ptr = str;
  while (*ptr) {
    // printf("%d %c|", *ptr, *ptr);

    if (*ptr >= 97 && *ptr <= 122)
      *ptr = *ptr - 32;

    ptr++;
  }
}

double pow2(int n, int p) {
  double val = n;
  int _p = p > 0
               ? p
               : -1 * p + 2;

  for (int i = 1; i < _p; i++) {
    if (p > 0)
      val *= n;
    else
      val /= n;
  }

  return val;
}

#include <ctype.h>
#include <stdio.h>

const size_t STR_SIZE = 255;

// function prototype (only if func is not defined immediately)
void hi(void);
void echo(void);
void parse(char *);
void parse2nums(int *, int *);
void upper(char *);
void swap(int *, int *);
double pow2(int n, int p);

/*
  parameters are passed by value (copies) and does not modify the argument passed
  passing by pointer will modify the argument

  Note:
    theres no default values for functions in C
    function variables are local and is destroyed after call
    functions can not access variables outside its scope, only values passed
*/

int main() {
  char str[STR_SIZE];
  double num;
  int x, y;

  printf("%s\n", str);

  // hi();
  // echo();
  // parse(str);
  // upper(str);
  // parse2nums(&x, &y);

  return 0;
}

void hi(void) {
  printf("\nHello, World!\n");
}

void echo(void) {
  printf("echo a string: ");
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    putchar(c);
  printf("\n%d\n", EOF);
}

void parse(char *str) {
  printf("enter string: ");
  fgets(str, STR_SIZE, stdin);
}

void parse2nums(int *x, int *y) {
  printf("enter 2 nums (pow): ");

  // can overflow (seg fault)
  scanf("%d %d", x, y);
  printf("%d %d\n", *x, *y);
  swap(x, y);
  printf("%d %d\n", *x, *y);

  printf("%.3f\n\n", pow2(*x, *y));
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

void swap(int *x, int *y) {
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

double pow2(int n, int p) {
  double val = n;
  int _p = p > 0 ? p : -1 * p + 2;

  for (int i = 1; i < _p; i++) {
    if (p > 0)
      val *= n;
    else
      val /= n;
  }

  return val;
}

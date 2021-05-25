#include <stdio.h>
#include <ctype.h>

const int STR_SIZE = 256;

// function prototype (only if func is not defined immediately)
void hi(void);
void echo(void);
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

int main() {
  char str[STR_SIZE];
  double num;
  int x, y;

  hi();
  echo();
  parse(str);
  upper(str);
  printf("\n%s", str);

  printf("enter 2 nums (pow): ");
  scanf("%d %d", &x, &y);
  num = pow2(x, y);
  printf("%f\n\n", num);

  return 0;
}

void hi(void) {
  printf("\nHello, World!\n");
}

void echo(void) {
  printf("echo a string: ");
  char c;
  do {
    c = getchar();
    putchar(c);
  } while (c != '\n');
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

#include <math.h>
#include <stdio.h>

const int MAX_STR_SIZE = 64;

int main() {
  int rows;
  float x;

  // string buffers
  char cmd[20];
  char args[MAX_STR_SIZE];

  /*
    only parses first whitespace separated string
    can overflow size of array
    array is already a pointer to the address so no need for &
  */
  printf("command: ");
  scanf("%s", cmd);

  /*
    reads files or stdin
    will not overflow
  */
  fgets(args, MAX_STR_SIZE, stdin);
  printf("%s %s\n\n", cmd, args);

  printf("How many rows: ");
  scanf("%d", &rows); // address of variable
  printf("%d\n\n", rows);

  for (int i = 0; i < rows; i++) {
    printf("%d\t", i);
    for (int j = i; j < 24; j++)
      printf("%c ", j + 65);

    printf("\n------------------------\n");
  }

  printf("\n\nsquare root: ");
  scanf("%f", &x);
  printf("%f\n", sqrt(x));

  printf("\n\n2 power: ");
  scanf("%f", &x);
  printf("%f\n", pow(2, x));

  return 0;
}

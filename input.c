#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const size_t MAX_STR_SIZE = 64;

char *parseInput(void);
void printRows(int);

int main() {
  int rows;
  float x;
  char *input_1;

  char cmd[20];
  char args[MAX_STR_SIZE];

  input_1 = parseInput();
  printf("%s", input_1);

  free(input_1);
  input_1 = NULL;

  /*
    scanf only parses up to the first whitespace, tab, newline or EOF
    may overflow buffer
  */
  printf("command: ");
  // scanf("%s", cmd);

  // up to 19 chars or first whitespace
  // scanf("%19s", cmd);

  // up to 19 chars or first newline
  scanf("%19[^\n]", cmd);

  // reads files or stdin, up to specified size - 1, newline or EOF, appends \0
  fgets(args, MAX_STR_SIZE, stdin);
  printf("%s %s\n\n", cmd, args);

  // printf("How many rows: ");
  // scanf("%d", &rows);
  // printRows(rows);

  // printf("\n\nsquare root: ");
  // scanf("%f", &x);
  // printf("%f\n", sqrt(x));

  // printf("\n\n2 power: ");
  // scanf("%f", &x);
  // printf("%f\n", pow(2, x));

  return 0;
}

void printRows(int c) {
  for (int i = 0; i < c; i++) {
    printf("%d\t", i);
    for (int j = i; j < 26; j++)
      printf("%c ", j + 65);

    printf("\n------------------------\n");
  }
}

char *parseInput() {
  char *input = malloc(sizeof(char) * MAX_STR_SIZE);
  if (input == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }

  printf("Enter input: ");
  fgets(input, MAX_STR_SIZE, stdin);
  return (char *)memmove(input, input, strlen(input));
}

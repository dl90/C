#include <stdio.h>
#include <stdlib.h>

char *parseInput(void);
int strCompare(char *a, char *b);
char *strCopy(char *src);

const int MAX_STR_SIZE = 255;

int main(void) {

  char *input_1 = parseInput();
  char *input_2 = parseInput();

  printf("%s", input_1);
  printf("%s", input_2);

  printf(strCompare(input_1, input_2) == 0 ? "equal\n" : "not equal\n");

  char *cpy = strCopy(input_1);
  printf("%s", cpy);
  printf(strCompare(input_1, cpy) == 0 ? "equal\n" : "not equal\n");

  free(input_1);
  free(input_2);
  free(cpy);
  input_1 = NULL;
  input_2 = NULL;
  cpy = NULL;
}

char *parseInput(void) {
  char *input = malloc(sizeof(char) * MAX_STR_SIZE);
  if (input == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }

  printf("Enter input: ");
  fgets(input, MAX_STR_SIZE, stdin);
  return input;
}

int strCompare(char *a, char *b) {
  int i = 0;

  while (a[i] != '\0' && b[i] != '\0') {
    if (a[i] != b[i])
      return 1;
    i++;
  }

  return 0;
}

char *strCopy(char *src) {
  int len = 1;
  while (src[len] != '\0')
    len++;

  char *dest = malloc(sizeof(char) * len);
  if (dest == NULL) {
    printf("Failed to allocate memory\n");
    exit(1);
  }

  for (int i = 0; i < len; i++) {
    dest[i] = src[i];
  }

  return dest;
}
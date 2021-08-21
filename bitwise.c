#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char BIT_LEN = 64;

// unsigned long long (2 ^ 64 - 1), bit length + 1 string termination
void int2BinaryStr(unsigned long long n, char *bin);
unsigned long long parseNum();

int main() {

  char *bin;

  bin = malloc(sizeof(char) * (BIT_LEN + 1));
  if (bin == NULL) {
    printf("bin memory error\n");
    return 1;
  }

  // int2BinaryStr(18446744073709551615U, bin);
  // printf("%s\n", bin);

  unsigned long long parsed = parseNum();
  int2BinaryStr(parsed, bin);
  printf("%s\n", bin);

  free(bin);

  return 0;
}

void int2BinaryStr(unsigned long long n, char *bin) {
  for (int i = BIT_LEN; i >= 0; i--) {
    bin[i] = n & 1 ? '1' : '0';
    n >>= 1;
  }
  bin[BIT_LEN + 1] = '\0';
}

unsigned long long parseNum() {
  char *input = malloc(sizeof(char) * 21);
  if (input == NULL) {
    printf("input memory error\n");
    exit(1);
  }

  printf("Enter up to 20 digits: ");
  fgets(input, 21, stdin);

  char *end;
  unsigned long long p = strtoull(input, &end, 10);

  const bool range_error = errno == ERANGE;
  if (range_error)
    printf(" Range error occurred.\n");

  return p;
}

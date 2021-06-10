#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char BIT_LEN = 64;

// unsigned long long (2 ^ 64 - 1), bit length + 1 string termination
void int2BinaryStr(unsigned long long n, char *bin);

int main() {

  char *bin;

  bin = malloc(sizeof(char) * (BIT_LEN + 1));
  if (bin == NULL) {
    printf("bin memory error\n");
    return 1;
  }

  int2BinaryStr(18446744073709551615U, bin);
  printf("%s\n", bin);

  return 0;
}

void int2BinaryStr(unsigned long long n, char *bin) {
  for (int i = BIT_LEN; i >= 0; i--) {
    bin[i] = n & 1 ? '1' : '0';
    n >>= 1;
  }
  bin[BIT_LEN + 1] = '\0';
}

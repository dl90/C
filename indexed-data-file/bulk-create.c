#include "_funcs.h"
#include "_types.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long fileSize(FILE *);

int main(void) {

  Person people[] = {
      {"Moe", "Howard", 83},
      {"Larry", "Fine", 81},
      {"Curley", "Howard", 79},
      {"Robin", "Williams", 61},
      {"Larry", "Sanders", 60},
      {"Howard", "Stern", 58},
      {"Steven", "Wright", 56},
      {"Harrison", "Andrew", 58},
      {"Harrison", "Ford", 63},
      {"Elton", "John", 63}};

  FILE *fp = fopen(DATA_FILE_NAME, "wb");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }

  // bulk write
  fwrite(people, sizeof(Person), sizeof(people) / sizeof(Person), fp);
  printf("File written \nstruct size: %lu \nfile size: %ld\n", sizeof(Person), getFileSize(fp));

  fclose(fp);
}

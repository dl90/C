#ifndef FUNCS_H
#define FUNCS_H
#include <stdio.h>

const char *const DATA_FILE_NAME = "people.dat";
const char *const INDEX_FILE_NAME = "people.idx";

unsigned long getFileSize(FILE *input) {
  unsigned long orgPos;
  unsigned long startPos;
  unsigned long endPos;

  // save file ptr position
  orgPos = ftell(input);

  rewind(input);
  startPos = ftell(input);
  fseek(input, 0, SEEK_END);
  endPos = ftell(input);

  // restore file ptr position
  fseek(input, orgPos, SEEK_SET);

  return endPos - startPos;
}

#endif

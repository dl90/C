#include "_funcs.h"
#include "_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IndexKey indexKey;

int main(void) {

  FILE *dataFile = fopen(DATA_FILE_NAME, "rb");
  FILE *indexFile = fopen(INDEX_FILE_NAME, "rb");
  if (dataFile == NULL || indexFile == NULL) {
    printf("Error opening files\n");
    exit(EXIT_FAILURE);
  }

  unsigned long recCount = getFileSize(dataFile) / sizeof(Person);
  IndexHeader indexHeader;
  IndexRecord indexRecord;
  int readCount = -1;

  readCount = fread(&indexHeader, sizeof(IndexHeader), 1, indexFile);

  if (readCount != 1) {
    printf("Error reading index header\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(indexHeader.fileName, DATA_FILE_NAME) != 0) {
    printf("ERROR - Data and Index File mismatch\n");
    fclose(dataFile);
    fclose(indexFile);
    exit(EXIT_FAILURE);
  }

  if (indexHeader.recCount != recCount) {
    printf("ERROR - Data and Index File record count do not match\n");
    fclose(dataFile);
    fclose(indexFile);
    exit(EXIT_FAILURE);
  }

  printf("\nData file indexed by ");
  switch (indexHeader.idxKey) {
  case FIRST:
    printf("first name\n\n");
    break;
  case LAST:
    printf("last name\n\n");
    break;
  case YEAR:
    printf("year\n\n");
    break;
  }
  printf("%-20s%-20s%6s\n", "First Name", "Last Name", "Age");
  printf("----------------------------------------------\n");

  Person temp = {"", "", 0};
  readCount = fread(&indexRecord, sizeof(IndexRecord), 1, indexFile);
  while (!feof(indexFile) && readCount == 1) {

    // place datafile pointer to indexed file position
    if (fseek(dataFile, indexRecord.filePos, SEEK_SET) != 0) {
      printf("Seek Error\n");
      fclose(dataFile);
      fclose(indexFile);
      exit(EXIT_FAILURE);
    }

    fread(&temp, sizeof(Person), 1, dataFile);
    printf("%-20s%-20s%6d\n", temp.firstName, temp.lastName, temp.age);

    readCount = fread(&indexRecord, sizeof(IndexRecord), 1, indexFile);
  }

  puts("");
  fclose(dataFile);
  fclose(indexFile);
}

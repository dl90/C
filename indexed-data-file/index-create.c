#include "_funcs.h"
#include "_types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IndexKey keySelector(void);
void readToMem(FILE *, IndexRecord *, int count);
int compare(const void *, const void *);

IndexKey keyType;

int main(void) {

  keyType = keySelector();

  FILE *dataFile = fopen(DATA_FILE_NAME, "rb");
  FILE *indexFile = fopen(INDEX_FILE_NAME, "wb");
  if (dataFile == NULL || indexFile == NULL) {
    printf("Error opening files\n");
    exit(EXIT_FAILURE);
  }

  unsigned long fileSize = getFileSize(dataFile);
  unsigned long recCount = fileSize / sizeof(Person);

  IndexRecord *inMemRecs = (IndexRecord *)calloc(recCount, sizeof(IndexRecord));
  if (inMemRecs == NULL) {
    printf("Error allocating memory\n");
    exit(EXIT_FAILURE);
  }

  readToMem(dataFile, inMemRecs, recCount);
  qsort(inMemRecs, recCount, sizeof(IndexRecord), compare);

  int writeCount;
  IndexHeader indexHeader = {.idxKey = keyType, .fileName = "", .recCount = recCount};
  strcpy(indexHeader.fileName, DATA_FILE_NAME);

  writeCount = fwrite(&indexHeader, sizeof(IndexHeader), 1, indexFile);
  if (writeCount != 1) {
    printf("Error writing index header\n");
    exit(EXIT_FAILURE);
  }

  writeCount = fwrite(inMemRecs, sizeof(IndexRecord), recCount, indexFile);
  if (writeCount != recCount) {
    printf("Error writing index records\n");
    exit(EXIT_FAILURE);
  }

  printf("\n%lu Records Processed\n", writeCount);
  puts("");
  printf("Index Record size = %lu\n", sizeof(IndexRecord));
  printf("Data Record size = %lu\n", sizeof(Person));
  printf("Data file size = %lu\n", fileSize);
  puts("");
  printf("Index Header size: %lu\n", sizeof(indexHeader));
  printf("Index Record size: %lu\n", sizeof(IndexRecord) * recCount);
  printf("Index file size: %lu\n\n", getFileSize(indexFile));

  free(inMemRecs);
  fclose(dataFile);
  fclose(indexFile);
}

IndexKey keySelector(void) {
  int op;

  do {
    printf("\n"
           "1: Index by first name\n"
           "2: Index by last name\n"
           "3: Index by age\n"
           "? ");

    scanf("%d", &op);
  } while (op < 1 || op > 3);

  return (IndexKey)(op - 1);
}

void readToMem(FILE *dataFile, IndexRecord *inMemRecs, int recCount) {
  Person temp = {"", "", 0};

  rewind(dataFile);
  long currFilePos = ftell(dataFile);
  unsigned int i = 0;
  int readCount = 0;

  readCount = fread(&temp, sizeof(Person), 1, dataFile);
  while (!feof(dataFile) && (readCount == 1)) {

    switch (keyType) {
    case FIRST:
      strcpy(inMemRecs[i].key.first, temp.firstName);
      break;
    case LAST:
      strcpy(inMemRecs[i].key.last, temp.lastName);
      break;
    case YEAR:
      inMemRecs[i].key.age = temp.age;
      break;
    }

    inMemRecs[i].filePos = currFilePos;
    ++i;
    currFilePos = ftell(dataFile);
    readCount = fread(&temp, sizeof(Person), 1, dataFile);
  }
}

int compare(const void *left, const void *right) {

  IndexRecord *pLeft = (IndexRecord *)left;
  IndexRecord *pRight = (IndexRecord *)right;
  int result;

  if (keyType == FIRST) {
    result = strcmp(pLeft->key.first, pRight->key.first);
    if (result == 0) {
      result = strcmp(pLeft->key.last, pRight->key.last);
    }
  } else if (keyType == LAST) {
    result = strcmp(pLeft->key.last, pRight->key.last);
    if (result == 0) {
      result = strcmp(pLeft->key.first, pRight->key.first);
    }
  } else if (keyType == YEAR) {
    result = pLeft->key.age - pRight->key.age;
    if (result == 0) {
      result = strcmp(pLeft->key.last, pRight->key.last);
    }
  }

  return result;
}
#ifndef TYPES_H
#define TYPES_H

typedef struct {
  char firstName[30];
  char lastName[30];
  int age;
} Person;

// variable index key types (union: shared 30 bytes)
typedef union {
  char first[30];
  char last[30];
  int age;
} KeyType;

// records for indexing data file
typedef struct {
  KeyType key;
  long filePos;
} IndexRecord;

// indicates KeyType used
typedef enum {
  FIRST,
  LAST,
  YEAR
} IndexKey;

// index file header for metadata
typedef struct {
  IndexKey idxKey;
  char fileName[30];
  unsigned long recCount;
} IndexHeader;

#endif

#include <stdio.h>

struct clientData {
  int acctNum;        // 4 Bytes
  char lastName[15];  // 15 Bytes
  char firstName[10]; // 10 Bytes
  double balance;     // 8 Bytes
};
// lastname and firstname are 25 bytes but are padded to 28 bytes for ds alignment (to 4)

typedef struct clientData ClientData;

int main(void) {
  int counter;

  ClientData blankClient = {0, "", "", 0.0};

  // creates write strream to random access file (raw data file)
  FILE *cfPtr = fopen("credit.dat", "wb");
  if (cfPtr == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  printf("Struct size: %lu\n", sizeof(ClientData));

  // output 100 blank records to file
  for (counter = 0; counter < 100; counter++) {
    fwrite(&blankClient, sizeof(ClientData), 1, cfPtr);
  }

  printf("Data file created.\n");

  fclose(cfPtr);
  return 0;
}

#include <stdio.h>

struct clientData {
  int acctNum;
  char lastName[15];
  char firstName[10];
  double balance;
};

typedef struct clientData ClientData;

int main(void) {
  FILE *cfPtr = fopen("credit.dat", "rb+");
  if (cfPtr == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  ClientData client = {0, "", "", 0.0};

  printf("Enter account number ( 1 to 100, 0 to end input )\n? ");
  scanf("%d", &client.acctNum);
  fflush(stdin);

  while (client.acctNum != 0) {
    printf("Enter lastname firstname balance (separated by spaces)\n? ");

    fscanf(stdin, "%s%s%lf", client.lastName, client.firstName, &client.balance);

    // seek position in file to user-specified record
    fseek(cfPtr, (client.acctNum - 1) * sizeof(struct clientData), SEEK_SET);

    // write user-specified information to file
    fwrite(&client, sizeof(struct clientData), 1, cfPtr);

    printf("Enter account number\n? ( 1 to 100, 0 to end input )\n? ");
    scanf("%d", &client.acctNum);
    fflush(stdin);
  }

  fclose(cfPtr);
  return 0;
}
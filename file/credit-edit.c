#include <stdio.h>

struct clientData {
  int acctNum;
  char lastName[15];
  char firstName[10];
  double balance;
};

typedef struct clientData ClientData;

int enterChoice(void);
void textFile(FILE *readPtr);
void updateRecord(FILE *fPtr);
void newRecord(FILE *fPtr);
void deleteRecord(FILE *fPtr);
void sumRecord(FILE *fPtr);
double bonusDebit(FILE *filePtr, double debitAmount);

int main(void) {
  FILE *cfPtr = fopen("credit.dat", "rb+");
  int choice;

  if (cfPtr == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  while ((choice = enterChoice()) != 0) {
    switch (choice) {
    case 1:
      textFile(cfPtr);
      break;

    case 2:
      updateRecord(cfPtr);
      break;

    case 3:
      newRecord(cfPtr);
      break;

    case 4:
      deleteRecord(cfPtr);
      break;

    case 5:
      sumRecord(cfPtr);
      break;

    case 6:
      bonusDebit(cfPtr, 10.00);
      break;

    default:
      printf("Incorrect choice\n");
      break;
    }
  }

  fclose(cfPtr);
  return 0;
}

void textFile(FILE *readPtr) {
  FILE *writePtr = fopen("accounts.txt", "w");
  if (writePtr == NULL) {
    printf("Error opening file.\n");
    return;
  }

  ClientData client = {0, "", "", 0.0};

  rewind(readPtr); // sets pointer to beginning of file
  fprintf(writePtr, "%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

  // Read first record
  fread(&client, sizeof(ClientData), 1, readPtr);

  while (!feof(readPtr)) {
    if (client.acctNum != 0) {
      fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    }

    // Read next record
    fread(&client, sizeof(ClientData), 1, readPtr);
  }

  fclose(writePtr);
}

void updateRecord(FILE *fPtr) {
  int account;
  double transaction;

  ClientData client = {0, "", "", 0.0};

  printf("Enter account to update ( 1 - 100 ): ");
  scanf("%d", &account);
  fflush(stdin);

  // move file pointer to correct record in file
  fseek(fPtr, (account - 1) * sizeof(ClientData), SEEK_SET);

  // read record from file
  fread(&client, sizeof(ClientData), 1, fPtr);
  if (client.acctNum == 0) {
    printf("Account #%d does not exist.\n", account);
    return;
  }

  printf("%-6d%-16s%-11s%10.2f\n\n", client.acctNum, client.lastName, client.firstName, client.balance);

  // request transaction amount from user
  printf("Enter charge ( + ) or payment ( - ): ");
  scanf("%lf", &transaction);
  fflush(stdin);
  client.balance += transaction;

  printf("%-6d%-16s%-11s%10.2f\n\n", client.acctNum, client.lastName, client.firstName, client.balance);

  // move file pointer to correct record in file
  fseek(fPtr, (account - 1) * sizeof(ClientData), SEEK_SET);

  // write updated record over old record in file
  fwrite(&client, sizeof(ClientData), 1, fPtr);
}

void deleteRecord(FILE *fPtr) {
  ClientData client;
  ClientData blankClient = {0, "", "", 0};

  int accountNum;

  // obtain number of account to delete
  printf("Enter account number to delete ( 1 - 100 ): ");
  scanf("%d", &accountNum);
  fflush(stdin);

  // move file pointer to correct record in file
  fseek(fPtr, (accountNum - 1) * sizeof(ClientData), SEEK_SET);

  fread(&client, sizeof(ClientData), 1, fPtr);
  if (client.acctNum == 0) {
    printf("Account %d does not exist.\n", accountNum);
    return;
  }

  fseek(fPtr, (accountNum - 1) * sizeof(ClientData), SEEK_SET);

  // replace existing record with blank record
  fwrite(&blankClient, sizeof(ClientData), 1, fPtr);
}

void newRecord(FILE *fPtr) {
  ClientData client = {0, "", "", 0.0};

  int accountNum;

  printf("Enter new account number ( 1 - 100 ): ");
  scanf("%d", &accountNum);
  fflush(stdin);

  fseek(fPtr, (accountNum - 1) * sizeof(ClientData), SEEK_SET);

  // read record from file
  fread(&client, sizeof(ClientData), 1, fPtr);

  // display error if account already exists
  if (client.acctNum != 0) {
    printf("Account #%d already contains data.\n", client.acctNum);
    return;
  }

  printf("Enter lastname firstname balance (separated by spaces)\n? ");
  scanf("%s%s%lf", &client.lastName, &client.firstName, &client.balance);

  fflush(stdin);
  client.acctNum = accountNum;

  fseek(fPtr, (client.acctNum - 1) * sizeof(ClientData), SEEK_SET);
  fwrite(&client, sizeof(ClientData), 1, fPtr);
}

void sumRecord(FILE *readPtr) {
  double sum = 0;
  ClientData client = {0, "", "", 0.0};

  FILE *writePtr = fopen("sumreport.txt", "w");
  if (writePtr == NULL) {
    printf("Error opening file.\n");
    return;
  }

  rewind(readPtr);

  // column headers
  fprintf(writePtr, "%-6s%-16s%-11s%10s\n", "Acct", "Last Name", "First Name", "Balance");

  while (!feof(readPtr)) {
    if (client.acctNum != 0) {
      sum += client.balance;
      fprintf(writePtr, "%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
    }

    // Read next record
    fread(&client, sizeof(ClientData), 1, readPtr);
  }

  fprintf(writePtr, "\n%10.2f\n", sum);
  fclose(writePtr);
}

double bonusDebit(FILE *filePtr, double debitAmount) {
  double total = 0;
  ClientData client = {0, "", "", 0.0};

  rewind(filePtr);
  fread(&client, sizeof(ClientData), 1, filePtr);

  while (!feof(filePtr)) {
    if (client.acctNum != 0) {
      total += debitAmount;
      client.balance += debitAmount;

      fseek(filePtr, -1 * sizeof(ClientData), SEEK_CUR);
      fwrite(&client, sizeof(ClientData), 1, filePtr);
    }

    fread(&client, sizeof(ClientData), 1, filePtr);
  }

  printf("\n%10.2f\n", total);
  return total;
}

int enterChoice(void) {
  int menuChoice;

  printf("\nEnter your choice\n"
         "1 - store a formatted text file of accounts called \"accounts.txt\" for printing\n"
         "2 - update an account\n"
         "3 - add a new account\n"
         "4 - delete an account\n"
         "5 - Sum balances of all the accounts to sumreport.txt\n"
         "6 - Update accounts by adding a $10.00 debit amount\n"
         "\n0 - end program\n? ");

  scanf("%d", &menuChoice);
  fflush(stdin);
  return menuChoice;
}
#include <stdio.h>

int main(void) {

  int account;
  char name[30];
  double balance;

  int request;
  double sum = 0;

  FILE *cfPtr = fopen("clients.txt", "r");
  if (cfPtr == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  printf("Enter request\n"
         " 1 - List accounts with zero balances\n"
         " 2 - List accounts with credit balances\n"
         " 3 - List accounts with debit balances\n"
         " 4 - Sum balances of all the accounts and display result\n"
         " 5 - End program\n? ");
  scanf("%d", &request);
  fflush(stdin);

  while (request != 5) {
    // initial read
    fscanf(cfPtr, "%d%s%lf", &account, name, &balance);

    switch (request) {

    case 1:
      printf("\nAccounts with zero balances:\n");
      while (!feof(cfPtr)) {
        if (balance == 0)
          printf("%-10d%-13s%7.2f\n", account, name, balance);

        // read account, name and balance from file
        fscanf(cfPtr, "%d%s%lf", &account, name, &balance);
      }
      break;

    case 2:
      printf("\nAccounts with credit balances:\n");
      while (!feof(cfPtr)) {
        if (balance < 0)
          printf("%-10d%-13s%7.2f\n", account, name, balance);

        fscanf(cfPtr, "%d%s%lf", &account, name, &balance);
      }
      break;

    case 3:
      printf("\nAccounts with debit balances:\n");
      while (!feof(cfPtr)) {
        if (balance > 0)
          printf("%-10d%-13s%7.2f\n", account, name, balance);

        fscanf(cfPtr, "%d%s%lf", &account, name, &balance);
      }
      break;

    case 4:
      printf("\nList of all accounts:\n");
      while (!feof(cfPtr)) {
        sum += balance;

        printf("%-10d%-13s%7.2f\n", account, name, balance);
        fscanf(cfPtr, "%d%s%lf", &account, name, &balance);
      }

      printf("\nSum of all balances: ");
      printf("%7.2f\n", sum);
      break;
    }

    rewind(cfPtr); // return cfPtr to beginning of file

    printf("\n? ");
    scanf("%d", &request);
    fflush(stdin);
  }

  fclose(cfPtr);
  return 0;
}

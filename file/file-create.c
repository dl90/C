#include <stdio.h>

int main(void) {

  int account;
  char name[30];
  double balance;

  FILE *cfPtr;
  cfPtr = fopen("clients.txt", "w");

  if (cfPtr == NULL) {
    printf("Error opening file.\n");
    return 1;
  }

  printf("Enter the account name and balance. (separated by spaces)\n");
  printf("Enter EOF to end input. (Crtl-Z)\n");
  printf("? ");
  scanf("%d%s%lf", &account, name, &balance);
  fflush(stdin);

  while (!feof(stdin)) {
    fprintf(cfPtr, "%d %s %.2f\n", account, name, balance);
    printf("? ");
    scanf("%d%s%lf", &account, name, &balance);
  }

  fclose(cfPtr);

  return 0;
}
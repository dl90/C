#include <stdio.h>
#include <string.h>

/*
  # compile
  gcc fileName.c [-o binaryFileName]

  # run
  ./binaryFileName || a.out
*/

// constants
const int CONSTANT_VAR = 1;
#define NUM 20

// int add_two_nums(int num1, int num2);
// int add_two_nums(int num1, int num2) {
//   return num1 + num2;
// }

int main(void) {
  printf("%d Hello World\n\n", NUM);

  /*
    # type overflow
    need to verify bounds of each type
  */
  char i = 127;
  i += 10; // no complier warning for overflow
  printf("%u", i);

  /*
    # floating types

    float:        32 bits, 23 bit mantisa, 8 bit exponent
    double:       64 bits, 53 bit mantisa, 11 bit exponent
    long double:  80 bits, 64 bit mantisa, 15 bit exponent
   */
  printf("char size: %lu bytes\n", sizeof(char));
  printf("int size: %lu bytes\n", sizeof(int));
  printf("short size: %lu bytes\n", sizeof(short));
  printf("long size: %lu bytes\n", sizeof(long));
  printf("float size: %lu bytes\n", sizeof(float));
  printf("double size: %lu bytes\n", sizeof(double));
  printf("long double size: %lu bytes\n\n", sizeof(long double));

  /*
    # arrays

    must specify type and size during variable definition
    variable assigned is a pointer* to first ele
  */
  int a[5] = {1, 2, 3, 4, 5};
  int b[5];

  for (int i = 0; i < 5; i++) {
    b[i] = i * 2;
    printf("%d", b[i]);
  }
  printf("\n");

  for (int i = 0; i < 5; i++)
    printf("%u", *a + i);

  printf("\n----------\n");

  /*
    # strings

    are actually an array of char values
    one extra space is needed for string terminator '\0'
  */
  char hello_1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
  char hello_2[6] = "World";

  printf("%s %s\n", hello_1, hello_2);
  printf("%lu\n\n", strlen(hello_2));

  /*
    # pointers
  */
  int var_1;
  int *ptr_1 = &var_1; // creates new pointer, assigns address of age variable to pointer
  *ptr_1 = 37;         // dereference pointer, updates value at that address (age)
  printf("ptr addr %p\nptr val: %p\nvar addr: %p\nvar val: %d\nderef ptr val: %d\n\n",
         &ptr_1, ptr_1, &var_1, var_1, *ptr_1);

  char arr_1[8] = "abcdefg";
  for (int i = 0; i < sizeof(arr_1) / sizeof(arr_1[0]); i++)
    printf("%p\n", &arr_1[i]);

  printf("\n----------\n");

  char *ptr_2 = arr_1;
  printf("\nptr initial addr: %p\n\n", ptr_2);

  for (; ptr_2 < &arr_1[8]; ptr_2++) {
    printf("%p %c ", ptr_2, *ptr_2);

    char ltr = *ptr_2;
    if (ltr != '\0')
      *ptr_2 = ltr - 32;

    printf("%c\n", *ptr_2);
  }
  printf("\narr val %s\n", arr_1);
  printf("arr last ptr %p\n", &arr_1[8]);
  printf("ptr after addr: %p\n", ptr_2);

  return 0;
}

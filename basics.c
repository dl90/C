#include <stdio.h>
#include <string.h>

/*
  # compile
  {
    compile => object code/tokenized instructions,
    link    => adds C libraries to object code
  }
  gcc fileName.c [-o binaryFileName]
  cc
  clang
  c99
  make

  # run
  ./binaryFileName || a.out
*/

// constants (file scope/global definition)
#define NUM 20
const int CONSTANT_VAR = 1;

void floatSizes(void);
void typeOverflow(void);
void arrays(void);
void strings(void);
void pointers(void);
void arrayAddress(char[]);
void arrayPointer(char *);
void array2D(void);

int main() {
  // %d int format specifier
  printf("Hello World %d\n\n", NUM);

  // block scope definition (declaration + initialization)
  char arr_1[] = "abcdefg";

  // can be nested
  struct person {
    char *name;
    int age;
  };

  struct person a;
  struct person b = {"Joe", 40};
  a.name = "John";
  a.age = 30;

  printf("%lu\n", sizeof(struct person));
  printf("name: %s age: %d\n", a.name, a.age);
  printf("name: %s age: %d\n", b.name, b.age);

  /*
    variable declaration only associates an address to the variable
    there is not default variable value prior to initialization/assignment
    whatever value is in that memory will be the value of the variable
  */
  char s[50];
  printf("%s %lu\n", s, sizeof(s));

  // floatSizes();
  // typeOverflow();
  // arrays();
  // strings();
  // pointers();
  // arrayAddress(arr_1);
  // arrayPointer(&arr_1[0]);
  // printf("\n%s\n", arr_1);
  // array2D();

  return 0;
}

/*
  # floating types

  float:        32 bits, 23 bit mantisa, 8 bit exponent
  double:       64 bits, 53 bit mantisa, 11 bit exponent
  long double:  80 bits, 64 bit mantisa, 15 bit exponent
*/
void floatSizes() {
  printf("char size: %lu bytes\n", sizeof(char));
  printf("int size: %lu bytes\n", sizeof(int));
  printf("short size: %lu bytes\n", sizeof(short));
  printf("long size: %lu bytes\n", sizeof(long));
  printf("float size: %lu bytes\n", sizeof(float));
  printf("double size: %lu bytes\n", sizeof(double));
  printf("long double size: %lu bytes\n", sizeof(long double));
  printf("long long size: %lu bytes\n\n", sizeof(long long));
}

/*
  # type overflow
  need to verify bounds of each type
*/
void typeOverflow() {
  char i = 127;
  printf("original: %u\n", i);
  i += 10; // no complier warning for overflow
  printf("overflowed: %u\n\n", i);
}

/*
  # arrays

  must specify type and size during variable definition
  variable assigned is a pointer* to first ele
*/
void arrays() {
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
}

/*
  # strings

  are actually an array of char values
  one extra space is needed for string terminator '\0'

  char * => string
  char ** => array of strings
*/
void strings() {
  char hello_1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
  char hello_2[6] = "World";

  printf("%s %s\n", hello_1, hello_2);
  printf("%lu\n\n", strlen(hello_2));
}

/*
  # pointers

  variable contains a memory address
  &var returns address of variable
  *ptr dereference, refers to the data at the address
*/
void pointers() {
  int var_1;
  int *ptr_1 = NULL;
  int **ptr_ptr = NULL; // address of an int pointer

  ptr_1 = &var_1; // creates new pointer (ptr_1), assigns address of variable (var_1) to pointer
  *ptr_1 = 37;    // dereference pointer, updates value of variable at that address (var_1)

  ptr_ptr = &ptr_1; // pointer pointing to the address of a pointer
  **ptr_ptr = 35;   // dereferencing twice: ptr_ptr => ptr_1 => var_1

  printf("ptr addr %p\nptr val: %p\nvar addr: %p\nvar val: %d\nderef ptr val: %d\n\n",
         &ptr_1, ptr_1, &var_1, var_1, *ptr_1);
}

/*
  # array decay

  function parameters array types are adjusted to pointer types

  void func(int array[]);
  void func(int *array);
*/
void arrayAddress(char arr[]) {
  // int len = sizeof(arr) / sizeof(arr[0]);
  int len = strlen(arr);

  for (int i = 0; i < len + 1; i++)
    printf("%p %c\n", &arr[i], arr[i]);

  printf("\n----------\n");
}

void arrayPointer(char *p) {
  int len = strlen(p);

  printf("\nptr initial addr: %p\n", p);

  for (int i = 0; i < len; i++, p++) {
    printf("%p %c ", p, *p);

    char ltr = *p;
    if (ltr != '\0')
      *p = ltr - 32;

    printf("%c\n", *p);
  }

  printf("ptr after addr: %p\n", p);
}

void array2D() {
  int grid[3][3];
  int x, y;

  // initialization
  for (y = 0; y < 3; y++)
    for (x = 0; x < 3; x++)
      grid[y][x] = 0;

  grid[0][0] = 1;
  grid[1][1] = 1;
  grid[2][2] = 1;

  for (y = 0; y < 3; y++) {
    for (x = 0; x < 3; x++)
      printf("%d ", grid[y][x]);
    printf("\n");
  }
  printf("\n");

  char strs[3][16] = {
      "this",
      "is",
      "sparta"};

  for (y = 0; y < 3; y++)
    printf("%s ", strs[y]);
  printf("\n");
}

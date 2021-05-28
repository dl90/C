#include <stdio.h>
#include <string.h>

void func_1(char *ptr);
void func_2(const char *ptr);
void func_3(char *const ptr);
void func_4(const char *const ptr);
void func_5(char *const *const ptr);

int main() {
  char str[5] = {'a', 'b', 'c', 'd', '\0'};

  // func_1(str);
  // func_2(str);
  // func_3(str);
  // func_4(str);

  // printf("%p %s\n", str, str);

  char *str_1 = "abcd"; // readonly string literal, throws bus error when attempting to edit
  const char *str_2 = "abcd";
  printf("%p %p %d\n", str_1, str_2, str_1 == str_2);
  // func_2(str_1);
  // func_2(str_2);

  char *const s = str;
  char *const *const ss = &s;
  printf("%p => %p %p => %c\n", ss, *ss, s, *s);

  func_5(ss);
  printf("%s\n", s);

  return 0;
}

// mutable pointer to a mutable char
void func_1(char *str) {
  while (*str) {
    printf("%p %c\n", str, *str);
    *str = 'A';
    str++;
  }
}

// mutable pointer to a constant char
void func_2(const char *str) {
  while (*str) {
    printf("%p %c\n", str, *str);
    str++;
  }
}

// constant pointer to a mutable char
void func_3(char *const str) {
  char *tmp = str;
  while (*tmp) {
    printf("%p %c\n", tmp, *tmp);
    *tmp = 'A';
    tmp++;
  }
}

// constant pointer to constant char
void func_4(const char *const str) {
  // char *tmp = str; // throws qualifer warning
  // while (*tmp) {
  //   printf("%p %c\n", tmp, *tmp);
  //   tmp++;
  // }
  printf("%p %s\n", str, str);
}

// constant pointer to constant pointer to mutable char
void func_5(char *const *const str) {
  printf("%s\n", *str);
  func_3(*str);
}

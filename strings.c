#include <stdio.h>
#include <string.h>

#define STR_SIZE 64

void parse_print(char *);
void concat_str(char *, const char *);
void replace(char *, int, char *);

/*
  # char[] vs char*  (array vs pointer)

  both can be used for holding strings but are not the same
  complier knows the size of arrays

  a: | h | e | l | l | o |\0 |
  p: |  *======> | w | o | r | l | d |\0 |

  strings can not be directly assigned to a buffer after declaration
  must strcpy to a string buffer

  Note: string literals are readonly and exists through the whole program
  attempts to modify string literal data may result in unpredictable behaviour
  it is encouraged to assign string literals as const
*/
int main() {
  // const types are scoped within the body it is defined
  const char *strs = "some long string";
  char str_buffer[STR_SIZE];
  char *ptr_arr[3] = {"abc", "bcd", "cde"};

  for (int i = 0; i < sizeof(ptr_arr) / sizeof(ptr_arr[0]); i++) {
    printf("%p %s\n", ptr_arr[i], ptr_arr[i]);

    // pointer notation (same as ptr_arr[i])
    char *x = *(ptr_arr + i);
    while (*x) {
      printf("\t%p %c\n", x, *x);
      x++;
    }
  }

  // int len = strlen(strs);
  // printf("len: %d\n\n", len);

  parse_print(str_buffer);
  concat_str(str_buffer, strs);
  replace(str_buffer, 2, "insert");
}

void parse_print(char *str) {
  printf("input string: ");
  fgets(str, STR_SIZE, stdin);

  str[strcspn(str, "\n")] = 0;
  printf("%s\n", str);
}

/*
  can’t return local variable from a C function
  they automatically destroyed when the function finished execution

  best solution is to use a passsed buffer and do manipulations on that buffer
*/
void concat_str(char *buf, const char *str) {
  strcat(buf, " ");
  strcat(buf, str);
  printf("%s\n", buf);
}

void replace(char *buf, int idx, char *str) {
  if (idx < STR_SIZE) {
    int len = strlen(str);
    for (int i = idx; i < len + idx; i++) {
      buf[i] = *str;
      str++;
    }
  }
  printf("%s\n", buf);
}

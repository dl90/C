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

  int len = strlen(strs);
  printf("len: %d\n\n", len);
  parse_print(str_buffer);

  concat_str(str_buffer, strs);
  printf("%s\n", str_buffer);

  replace(str_buffer, 2, "insert");
  printf("%s\n", str_buffer);
}

void parse_print(char *str) {
  printf("input string: ");
  fgets(str, STR_SIZE, stdin);

  str[strcspn(str, "\n")] = 0;
  printf("%s\n\n", str);
}

/*
  can’t return local variable from a C function
  they automatically destroyed when the function finished execution

  best solution is to use a passsed buffer and do manipulations on that buffer
*/
void concat_str(char *buf, const char *str) {
  strcat(buf, " ");
  strcat(buf, str);
}

void replace(char *buf, int idx, char *str) {
  if (idx < STR_SIZE) {
    int len = strlen(str);
    for (int i = idx; i < len + idx; i++) {
      buf[i] = *str;
      str++;
    }
  }
}

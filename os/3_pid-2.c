#include <stdio.h>
#include <unistd.h>

int global = 0;

int main(void) {

  int status;
  pid_t fork_return = fork();

  if (fork_return == 0) {
    printf("global child: %d\n", global);
  } else {
    global++;
    printf("global: %d\n", global);
  }

  sleep(1);
  return 0;
}

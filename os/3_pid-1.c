#include <stdio.h>
#include <unistd.h>

int main(void) {

  pid_t fork_return = fork();
  pid_t pid = getpid();

  printf("fork return: %d\npid: %d\n", fork_return, pid);
  sleep(1);
  return 0;
}

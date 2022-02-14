#include <stdio.h>
#include <unistd.h>

// cat /proc/<pid>/maps
int main(void) {

  pid_t pid = getpid();
  printf("pid: %d\n", pid);
  fflush(stdout);

  sleep(1200);
  return 0;
}

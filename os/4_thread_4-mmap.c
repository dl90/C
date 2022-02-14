#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

char ptype[10];

int main(void) {

  int size = 50 * sizeof(int);
  void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    return 1;
  }
  printf("mapped at: %p\n\n", ptr);

  int *shared = ptr;
  int status;
  pid_t fork_ret = fork();
  if (fork_ret > 0) {
    shared[0] = 40;
    shared[1] = -20;
    strcpy(ptype, "parent");
    waitpid(-1, &status, 0);
  } else {
    sleep(1);
    printf("child [0]: %d [1]: %d\n", shared[0], shared[1]);
    shared[1] = 120;
    strcpy(ptype, "child");
  }

  printf("%s shared[0]: %d\n", ptype, shared[0]);
  printf("%s shared[1]: %d\n", ptype, shared[1]);
  munmap(ptr, size);
  return 0;
}

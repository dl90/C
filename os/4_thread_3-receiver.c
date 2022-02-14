#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct {
  long mtype;
  char mtext[BUFSIZ];
} msg_st;

int main(void) {

  int running = 1;
  int msg_id;
  msg_st msg;
  long msg_to_receive = 0;

  msg_id = msgget((key_t)1234, 0666 | IPC_CREAT);
  if (msg_id == -1) {
    fprintf(stderr, "msgget failed with error: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  while (running) {
    if (msgrcv(msg_id, (void *)&msg, BUFSIZ, msg_to_receive, 0) == -1) {
      fprintf(stderr, "msgrcv failed with error: %d\n", errno);
      exit(EXIT_FAILURE);
    }

    printf("you wrote: %s", msg.mtext);

    if (strncmp(msg.mtext, "end", 3) == 0)
      running = 0;

    if (msgctl(msg_id, IPC_RMID, 0) == -1) {
      fprintf(stderr, "msgctl (IPC_RMID) failed with error: %d\n", errno);
      exit(EXIT_FAILURE);
    }
  }
  exit(EXIT_SUCCESS);
}

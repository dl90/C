#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 512
int msg_count = 5;

typedef struct {
  long mtype;
  char mtext[MAX_TEXT];
} msg_st;

int main(int argc, char *argv[]) {

  if (argc == 2)
    msg_count = atoi(argv[1]);

  msg_st msg;
  int msg_id;
  char buffer[MAX_TEXT];

  msg_id = msgget((key_t)1234, 0666 | IPC_CREAT);
  if (msg_id == -1) {
    fprintf(stderr, "msgget failed with error: %d\n", errno);
    exit(EXIT_FAILURE);
  }

  for (int i = 1; i <= msg_count; i++) {
    msg.mtype = 1;
    sprintf(msg.mtext, "message [%d] sent\n", i);

    if (i == msg_count)
      sprintf(msg.mtext, "end\n");

    printf("message [%i] sent\n", i);

    if (msgsnd(msg_id, (void *)&msg, MAX_TEXT, 0) == -1) {
      fprintf(stderr, "msgsnd failed with error: %d\n", errno);
      exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}
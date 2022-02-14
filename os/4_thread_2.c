#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *method_1(void *arg);
void *method_2(void *arg);

int counter = 0;

int main(int argc, char *argv[]) {
  pthread_t thread_1;
  pthread_t thread_2;
  int th_1 = 1;
  int th_2 = 2;

  pthread_create(&thread_1, NULL, method_1, &th_1);
  pthread_create(&thread_2, NULL, method_2, &th_2);

  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);
  // sleep(2);
  return 0;
}

void *method_1(void *arg) {
  int *temp = (int *)arg;
  while (1) {
    sleep(1);
    counter++;
    printf("hello from %d\n", *temp);
    printf("thread: %d counter: %d\n", *temp, counter);
    printf("---------------------\n");
  }
  pthread_exit(NULL);
}

void *method_2(void *arg) {
  while (1) {
    int *temp = (int *)arg;
    sleep(1);
    printf("hello from %d\n", *temp);
    printf("thread: %d counter: %d\n", *temp, counter);
  }
  pthread_exit(NULL);
}

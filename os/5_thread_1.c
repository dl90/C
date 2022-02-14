#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;

void *countGold(void *param) {
  int *p = (int *)param;
  // pthread_mutex_lock(&m);
  for (int i = 0; i < 10000; i++) {
    sum += 1;
  }
  // pthread_mutex_unlock(&m);
  return NULL;
}

int main() {
  int thread_num_1 = 1;
  int thread_num_2 = 2;

  pthread_t tid_1, tid_2;
  pthread_create(&tid_1, NULL, countGold, &thread_num_1);
  pthread_create(&tid_2, NULL, countGold, &thread_num_2);

  pthread_join(tid_1, NULL);
  pthread_join(tid_2, NULL);
  printf("sum = %d\n", sum);
  return 0;
}

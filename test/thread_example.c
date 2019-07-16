/*
线程内存模型探究
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 2

void* thread(void*);

char **ptr;  // 全局变量

int main(int argc, char const *argv[])
{
  int i;
  pthread_t tid;
  char *msg[N] = {
    "Hello from ss",
    "Hello from 07"
  };
  ptr = msg;
  for (i = 0; i < N; i++) {
    pthread_create(&tid, NULL, thread, (void*)i);
  }
  pthread_join(tid, NULL);
  return 0;
}

void* thread(void* vargp) {
  int myid = (int)vargp;
  static int cnt = 0;
  printf("[%d]: %s (cnt=%d)\n", myid, ptr[myid], ++cnt);
  return NULL;
}
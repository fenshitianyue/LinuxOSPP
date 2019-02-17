#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter;
pthread_rwlock_t rwlock;

void* route_write(void* arg){
  int t = 0;
  int i = *(int*)arg;
  free(arg);
  while(1){
    t = counter;
    sleep(1);
    pthread_rwlock_wrlock(&rwlock);
    printf("write:%d:%#X: counter = %d ++counter = %d\n", i, pthread_self(), t, ++counter);
    pthread_rwlock_unlock(&rwlock);
    sleep(5);
  }
}

void* route_read(void* arg){
  int t;
  int i = *(int*)arg;
  free(arg);
  while(1){
    pthread_rwlock_wrlock(&rwlock);
    printf("read: %d:%#X: counter = %d\n", i, pthread_self(), counter);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  }
}

int main() {
  int i = 0; 
  pthread_t tid[8];
  pthread_rwlock_init(&rwlock, NULL);
  for(i = 0; i < 3; ++i){
    int* p = (int*)malloc(sizeof(int));
    *p = i;
    pthread_create(&tid[i], NULL, route_write, (void*)p);
  }
  for(i = 0; i < 5; ++i){
    int* p = (int*)malloc(sizeof(int));
    *p = i;
    pthread_create(&tid[i+3], NULL, route_read, (void*)p);
  }
  for(i = 0; i < 8; ++i){
    pthread_join(tid[i], NULL);
  }
  pthread_rwlock_destroy(&rwlock);
  return 0;
}

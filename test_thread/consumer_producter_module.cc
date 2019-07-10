#include <iostream>
#include <queue>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

#define NUM 8
#define CONSUMER_COUNT 2
#define PRODUCTER_COUNT 2

class BlockQueue{
private:
  std::queue<int> q;
  size_t cap;
  pthread_mutex_t lock;
  pthread_cond_t full;
  pthread_cond_t empty;
private:
  void LockQueue(){
    pthread_mutex_lock(&lock);
  }
  void UnLockQueue(){
    pthread_mutex_unlock(&lock);
  }
  void ProductWait(){
    pthread_cond_wait(&full, &lock);
  }
  void ConsumerWait(){
    pthread_cond_wait(&empty, &lock);
  }
  void NotifyProduct(){
    pthread_cond_signal(&full);
  }
  void NotifyConsummer(){
    pthread_cond_signal(&empty);
  }
  bool IsEmpty(){
    return q.size() == 0;
  }
  bool IsFull(){
    return q.size() == cap;
  }
public:
  BlockQueue(int _cap = NUM) : cap(_cap){
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
  }
  void PushData(const int& data){
    LockQueue();
    while(IsFull()){
      NotifyConsummer();
      std::cout << "queue full, notify consumer. product stop!" << std::endl;
      ProductWait();
    }
    q.push(data);
    NotifyConsummer();
    UnLockQueue();
  }
  void PopData(int& data){
    LockQueue();
    while(IsEmpty()){
      NotifyProduct();
      std::cout << "queue empty, notify producter. consummer stop!" << std::endl;
      ConsumerWait();
    }
    data = q.front();
    q.pop();
    NotifyProduct();
    UnLockQueue();
  }
  ~BlockQueue(){
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
  }
};

pthread_t threads[CONSUMER_COUNT + PRODUCTER_COUNT];

void* consumer(void* arg){
  BlockQueue* b = (BlockQueue*)arg;
  int data;
  while(true){
    b->PopData(data);
    std::cout << "Consum data done: " << data << std::endl;
  }
}

void* producter(void* arg){
  BlockQueue* b = (BlockQueue*)arg;
  srand((unsigned long)time(NULL));
  while(true){
    int data = rand() % 1024;
    b->PushData(data);
    std::cout << "Product data done: " << data << std::endl;
    sleep(1);
  }
}

int main(){
  BlockQueue b;
  for(int i = 0; i != CONSUMER_COUNT; ++i){
    pthread_create(&threads[i], NULL, consumer, (void*)&b);
  }
  for(int i = 0; i != PRODUCTER_COUNT; ++i){
    pthread_create(&threads[CONSUMER_COUNT + i], NULL, producter, (void*)&b);
  }

  for(int i = 0; i != (CONSUMER_COUNT + PRODUCTER_COUNT); ++i){
    pthread_join(threads[i], NULL);
  }
  return 0;
}

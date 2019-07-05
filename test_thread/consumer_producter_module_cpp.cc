#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unistd.h>

#define NUM 8

class BlockQueue{
private:
  std::queue<int> _q;
  size_t _cap;
  std::mutex _lock; //pthread_mutex_t lock;
  std::unique_lock<std::mutex> _lck;
  std::condition_variable _full; //pthread_cond_t full;
  std::condition_variable _empty; //pthread_cond_t empty;
private:
  void LockQueue(){
    _lock.lock(); //pthread_mutex_lock(&lock);
  }
  void UnLockQueue(){
    _lock.unlock(); //pthread_mutex_unlock(&lock);
  }
  void ProductWait(){
    _full.wait(_lck); //pthread_cond_wait(&full, &lock);
  }
  void ConsumerWait(){
    _empty.wait(_lck); //pthread_cond_wait(&empty, &lock);
  }
  void NotifyProduct(){
    _full.notify_one(); //pthread_cond_signal(&full);
  }
  void NotifyConsummer(){
    _empty.notify_one(); //pthread_cond_signal(&empty);
  }
  bool IsEmpty(){
    return _q.size() == 0;
  }
  bool IsFull(){
    return _q.size() == _cap;
  }
public:
  BlockQueue(int cap = NUM) : _cap(cap), _lck(_lock){ //TODO:这里关于_lck的初始化可能会出bug
    //pthread_mutex_init(&lock, NULL);
    //pthread_cond_init(&full, NULL);
    //pthread_cond_init(&empty, NULL);
  }
  void PushData(const int& data){
    LockQueue();
    while(IsFull()){
      NotifyConsummer();
      std::cout << "queue full, notify consumer. product stop!" << std::endl;
      ProductWait();
    }
    _q.push(data);
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
    data = _q.front();
    _q.pop();
    NotifyProduct();
    UnLockQueue();
  }
  //~BlockQueue(){
  //  pthread_mutex_destroy(&lock);
  //  pthread_cond_destroy(&full);
  //  pthread_cond_destroy(&empty);
  //}
};

void consumer(void* arg){
  BlockQueue* b = (BlockQueue*)arg;
  int data;
  while(true){
    b->PopData(data);
    std::cout << "Consum data done: " << data << std::endl;
  }
}

void producter(void* arg){
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
  //pthread_t c, p;
  //pthread_create(&c, NULL, consumer, (void*)&b);
  //pthread_create(&p, NULL, producter, (void*)&b);
  std::thread c(consumer, (void*)&b);
  std::thread p(producter, (void*)&b);

  //pthread_join(c, NULL);
  //pthread_join(p, NULL);
  c.join();
  p.join();
  return 0;
}

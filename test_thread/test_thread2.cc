#include <iostream>
#include <thread>

void change(int* a, int* b){
  *a = 1;
  *b = 2;
  std::cout << "a new data:" << *a << std::endl;
  std::cout << "b new data:" << *b << std::endl;
}

int main() {
  int a = 10;
  int b = 20;
  std::thread t(change, &a, &b);

  t.join();
  return 0;
}

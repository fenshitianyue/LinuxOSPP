#include <stdio.h>

int i = 1;

void func(){
  char arr[1024];
  printf("%d ", i);
  i++;
  func();
}

int main() {
  func(); 
  return 0;
}

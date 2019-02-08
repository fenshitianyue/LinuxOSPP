#include <stdio.h>
#include <unistd.h>


int main() {
  int count = 0;
  alarm(1);
  //打印 1s 循环多少次
  while(1){
    printf("count = %d\n", count);
    count++;
  }
  return 0;
}

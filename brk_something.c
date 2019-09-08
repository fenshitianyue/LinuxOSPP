#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test_brk() {
  void* p = sbrk(0);
  int* p1 = (int*)p;
  brk(p1 + 4); //分配 sizeof(int) * 4 个字节堆空间
  int i = 0;
  while(i < 5) {
    p1[i] = i * 10;
    ++i;
  }
  i = 0;
  while(i < 5) {
    printf("%d ", p1[i++]);
  }
  printf("\n");
}

void test_sbrk() {
  int* p1 = (int*)sbrk(4);
  *p1 = 10;
  int* p2 = (int*)sbrk(4);
  *p2 = 20;
  printf("p1 address in '%p'\n", p1);
  printf("p2 address in '%p'\n", p2);
  printf("p1 point the %d\n", *p1);
  printf("p2 point the %d\n", *p2);
}

void test_malloc() {
  int* p = NULL;
  p = (int*)malloc(sizeof(int) * 4); //分配 sizeof(int) * 4 个字节堆空间
  int i = 0;
  while(i < 5) {
    p[i] = i * 10;
    ++i;
  }
  i = 0;
  while(i < 5) {
    printf("%d ", p[i++]);
  }
  printf("\n");
  printf("p[5] = %d\n", p[9]);
}

int main() {
  test_sbrk();
  return 0;
}

#include <stdio.h>
#include <fcntl.h>

///////////////////////////////////////////////////////
// 将文件描述符 fd 设置成非阻塞式
///////////////////////////////////////////////////////

void SetNonBlock(int fd) {
  int f1 = fcntl(fd, F_GETFL);
  if(f1 < 0) {
    perror("fcntl");
    return;
  }
  fcntl(fd, F_SETFL, f1 | O_NONBLOCK);
}

int main() {
  
  return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>


int main() {
  struct pollfd poll_fd; 
  poll_fd.fd = 0;
  poll_fd.events = POLLIN;
  while(1) {
    int ret = poll(&poll_fd, 1, 3000); //timeout:3s
    if(ret < 0) {
      perror("poll");
      continue;
    } else if(0 == ret) {
      printf("poll timeout\n");
      continue;
    }
    if(poll_fd.revents == POLLIN) {
      char buf[1024] = {0};
      read(0, buf, sizeof(buf) - 1);
      printf("stdin: %s", buf);
    }
  }
  return 0;
}

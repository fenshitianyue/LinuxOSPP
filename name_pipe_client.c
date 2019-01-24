#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define ERR_EXIT(m) \
  do{\
    perror(m);\
    exit(EXIT_FAILURE);\
  }while(0)

int main(){
  int fd = open("mypipe", O_WRONLY);
  if(fd < 0){
    ERR_EXIT("open");
  }
  char buf[1024] = {0};
  while(1){
    printf("Please enter: ");
    fflush(stdout);
    ssize_t s = read(0, buf, sizeof(buf) - 1);
    if(s > 0){
      buf[s] = 0;
      write(fd, buf, strlen(buf));
    }else{
      ERR_EXIT("read");
    }
  }
  close(fd);
  return 0;
}

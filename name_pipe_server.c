#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
  do{\
    perror(m);\
    exit(EXIT_FAILURE);\
  }while(0)

int main(){
  umask(0);
  if(mkfifo("mypipe", 0644) < 0){
    ERR_EXIT("mkfifo");
  }
  int fd = open("mypipe", O_RDONLY);
  if(fd < 0){
    ERR_EXIT("open");
  }
  char buf[1024] = {0};
  while(1){
    printf("Please wait...\n");
    ssize_t s = read(fd, buf, sizeof(buf) - 1);
    if(s > 0){
      buf[s] = 0;
      printf("client: %s\n", buf);
    }else if(0 == s){
      printf("client exit, server exit now!\n");
      exit(EXIT_FAILURE);
    }else{
      ERR_EXIT("read");
    }
  } 
  close(fd);
  return 0;
}

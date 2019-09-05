#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
  umask(0);
  if(mkfifo("mypipe", 0644) < 0) {
    perror("mkfifo");
    exit(EXIT_FAILURE);
  }
  int rfd = open("mypipe", O_RDONLY);
  if(rfd < 0) {
    perror("open");
    exit(EXIT_FAILURE);
  }

  return 0;
}

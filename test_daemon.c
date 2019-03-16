#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef enum{FALSE, TRUE} _bool;

_bool daemonize(){
  pid_t pid = fork();
  if(pid < 0){
    return FALSE;
  }else if(pid < 0){
    exit(EXIT_SUCCESS);
  }
  umask(0);
  if(setsid() < 0){
    return FALSE;
  }
  if(chdir("/") < 0){
    return FALSE;
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  //不知道为什么这个会报错？
  open("/dev/null", O_RDONLY);
  open("/dev/null", O_RDWR);
  open("/dev/null", O_RDWR);
  return TRUE;
}

int main() {
  
  return 0;
}

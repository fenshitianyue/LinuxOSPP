#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sig_function(int signo){
  if(14 == signo){
    //do_something
  }
}

size_t mysleep(size_t nsecs){
  struct sigaction new, old;
  size_t unslept = 0;
  new.sa_handler = sig_function;
  sigemptyset(&new.sa_mask);
  new.sa_flags = 0;
  sigaction(SIGALRM, &new, &old);
  alarm(nsecs);
  pause();
  unslept = alarm(0);
  sigaction(SIGALRM, &old, NULL);
  return unslept;
}

int main() {
  size_t n = 0;
  while(1){
    if((n = mysleep(5)) > 0){
      printf("还剩%lu秒\n", n);
      break;
    }
    printf("5 seconds passed\n");
  } 
  return 0;
}

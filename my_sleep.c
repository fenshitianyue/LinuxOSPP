#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sig_alrm(int signo){

}

size_t mysleep(size_t nsecs){
  struct sigaction new, old;
  size_t unslept = 0;
  new.sa_handler = sig_alrm;
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
  while(1){
    mysleep(5);
    printf("5 seconds passed\n");
  } 
  return 0;
}

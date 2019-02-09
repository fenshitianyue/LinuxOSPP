//这个版本的sleep考虑了竞态条件
#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sig_function(int signo){
  if(14 == signo){
    //do something
  }
}

size_t mysleep(size_t nsecs){
  struct sigaction newact, oldact;
  sigset_t newmask, oldmask, suspmask;
  size_t unslept = 0;
  newact.sa_handler = sig_function;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  sigaction(SIGALRM, &newact, &oldact);

  sigemptyset(&newmask);
  sigaddset(&newmask, SIGALRM);
  sigprocmask(SIG_BLOCK, &newmask, &oldmask);
  alarm(nsecs);
  suspmask = oldmask; 
  sigdelset(&suspmask, SIGALRM);
  sigsuspend(&suspmask);
  unslept = alarm(0);
  sigaction(SIGALRM, &oldact, NULL);
  sigprocmask(SIG_SETMASK, &oldmask, NULL);
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

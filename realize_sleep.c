#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void sig_function(int signo){
  if(14 == signo){
    //do_something
  }
}

size_t my_sleep(size_t nsecs){
  struct sigaction newact, oldact;
  size_t unslept = 0;
  newact.sa_handler = sig_function;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  sigaction(SIGALRM, &newact, &oldact);
  alarm(nsecs);
  pause();
  unslept = alarm(0);
  sigaction(SIGALRM, &oldact, NULL);
  return unslept;
}

size_t my_sleep_pro(size_t times){
  size_t left_times = 0;
  struct sigaction newact, oldact;
  sigset_t newmask, oldmask, suspmask;
  newact.sa_handler = sig_function;
  newact.sa_flags = 0;
  sigemptyset(&newact.sa_mask);
  sigemptyset(&newmask);
  sigaction(SIGALRM, &newact, &oldact);
  sigaddset(&newmask, SIGALRM);
  sigprocmask(SIG_BLOCK, &newmask, &oldmask);

  alarm(times);

  suspmask = oldmask;
  sigdelset(&suspmask, SIGALRM);
  sigsuspend(&suspmask);
  left_times = alarm(0);

  sigaction(SIGALRM, &oldact, NULL);
  sigprocmask(SIG_SETMASK, &oldmask, NULL);
  return left_times;
}

int main() {
  while(1){
    printf("wait 5s...\n");
    my_sleep_pro(5);
  } 
  return 0;
}

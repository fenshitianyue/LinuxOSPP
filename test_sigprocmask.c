#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void print_sig_set(sigset_t* set){
  int i = 0;
  for(i = 1; i <= 34; ++i){
    if(sigismember(set, i)){
      putchar('1');
    }
    putchar('0');
  }
  puts("");
}

int main() {
  sigset_t s, p; 
  sigemptyset(&s);
  sigaddset(&s, SIGINT);
  sigprocmask(SIG_BLOCK, &s, NULL);
  while(1){
    sigpending(&p);
    print_sig_set(&p);
    sleep(1);
  }
  return 0;
}

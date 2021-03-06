#include "common.h"

int main() {
  int msgid = createMsgQueue();
  char buf[1024] = {0};  
  while(1) {
    printf("Please enter# ");
    fflush(stdout);
    ssize_t s = read(STDIN_FILENO, buf, sizeof(buf));
    if(s > 0) {
      buf[s - 1] = 0;
      sendMsg(msgid, CLIENT_TYPE, buf);
      printf("send done, wait recv...\n");
    }
    recvMsg(msgid, SERVER_TYPE, buf);
    printf("server# %s\n", buf);
  }
  destroyMsgQueue(msgid);
  return 0;
}

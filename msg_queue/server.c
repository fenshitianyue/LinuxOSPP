#include "common.h"

int main() {
  int msgid = createMsgQueue();
  char buf[1024] = {0};
  while(1) {
    recvMsg(msgid, CLIENT_TYPE, buf);
    printf("client# %s\n", buf);

    printf("Please enter# ");
    fflush(stdout);
    ssize_t s = read(STDIN_FILENO, buf, sizeof(buf));
    if(s > 0) {
      buf[s-1] = 0;
      sendMsg(msgid, SERVER_TYPE, buf);
      printf("send done, wait recv...\n");
    }
  }
  destroyMsgQueue(msgid);
  return 0;
}

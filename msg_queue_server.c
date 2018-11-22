#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

int main() {
  int id = msgget(1234, 0);
  if(-1 == id){
    perror("msgget");
    return 1;
  }
  struct msgbuf buf;
  while(1){
    memset(&buf, 0x00, sizeof(buf));
    msgrcv(id, &buf, 100, 1, 0);
    buf.mtype = *(long*)(buf.mtext);
    msgsnd(id, &buf, strlen(buf.mtext + sizeof(long)) + sizeof(long), 0);
    printf("send OK\n");
  }
  return 0;
}

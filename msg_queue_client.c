#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

/*
struct msgbuf{
  long mtype;
  char mtest[100];
};
*/

int main() {
  int id = msgget(1234, 0);
  if(id == -1){
    perror("msgget");
    return 1;
  }
  struct msgbuf buf;
  while(1){
    memset(&buf, 0x00, sizeof(buf));
    *(long*)(buf.mtext) = (long)getpid();
    buf.mtype = 1;
    scanf("%s", buf.mtext + sizeof(long));
    msgsnd(id, &buf, strlen(buf.mtext + sizeof(long)) + sizeof(long), 0);
    memset(&buf, 0x00, sizeof(buf));
    msgrcv(id, &buf, 100, getpid(), 0);
    printf("receive: %s\n", buf.mtext + sizeof(long));
  }
  return 0;
}

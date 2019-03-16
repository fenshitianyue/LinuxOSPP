#include <stdio.h>
#include <libgen.h>
//#include <string.h>

int main(int argc, char* argv[]) {
  if(argc != 3){
    printf("%s\n", basename(argv[0]));
  }else{
    printf("argv[0]: %s\n", argv[0]);
    printf("argv[1]: %s\n", argv[1]);
    printf("argv[2]: %s\n", argv[2]);
  }
  return 0;
}


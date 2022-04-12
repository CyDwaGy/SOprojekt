#include "mateusz.h"
#include "Filip.h"

#include <stdio.h>

int main(int arc,char * argv[]){
  char * source=argv[1];
  char * destiny=argv[2];
  toSleep(10);
  printf("%d\n",tryDelete(source,destiny));
  return 0;
}

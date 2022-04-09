#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char * argv[])
{
  int pid  = atoi(argv[1]);
  kill(pid, SIGUSR1);
  printf("Pobudzono proces o pidid: %d\n",pid);
  return 0;
}

#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
#include <signal.h>
#include "Filip.h"
#include "mateusz.h"
static volatile sig_atomic_t sig = 0;// zmienna do sprawdzania czy zostal wyslany sigusr1

void sig_handler_sigusr1(int signum){
  sig=signum;
}

int toSleep(int time);
int tryDelete(char * source, char * destiny){
 

 return 0;
}

int toSleep(int time){
  if(time<0)
    return -1;
  sig=0;
  signal(SIGUSR1,sig_handler_sigusr1); // zarejestrowanie Sygnalu
  printf("Sleep\n");
  sleep(time);
  if(sig!=0)
    printf("Wake up after SIGUSR1\n");
  else
    printf("Wake up after %ds\n",time);
  return 0;
}


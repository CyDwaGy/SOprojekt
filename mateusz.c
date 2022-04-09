#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void sig_handler_parent(int signum){
  printf("Parent : Received a response signal from child \n");
}

int main(){
  signal(SIGUSR1,sig_handler_parent); // Register signal handler
  sleep(1);
  printf("Parent: waiting for response\n");
  pause();
  return 0;
}

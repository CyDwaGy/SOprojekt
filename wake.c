#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc,char * argv[])
{
  char buf[512];
  //FILE *cmd_pipe = popen("pidof -s SyncMain", "r");
  FILE *cmd_pipe = popen("pidof -s mateusz", "r");
  fgets(buf, 512, cmd_pipe);
  pid_t pid = strtoul(buf, NULL, 10);
  pclose( cmd_pipe );
  if(argc>1)
    pid  = atoi(argv[1]);
  kill(pid, SIGUSR1);
  printf("Send SIGUSR1 to pid: %d\n",pid);
  return 0;
}

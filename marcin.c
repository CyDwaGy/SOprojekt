#include "marcin.h"
#include "mateusz.h"
#include "Filip.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
long long int CheckSize(char * fd){
  struct stat buf;
  stat(fd, &buf);
  int size=buf.st_size;
  return size;
}
int CopyMaly(char*pathF, char* pathT)
{
long long int size=CheckSize(pathF);
unsigned char * buffor;
int plikF= open(pathF, O_RDONLY);
int plikT = open( pathT, O_CREAT|O_WRONLY);
if (size<16384){
buffor = malloc(size);
read(plikF,buffor,size);
write(plikT,buffor,size);
}
else
{
while(size>16384)
   {
size-=16384;
buffor = malloc(16384);
read(plikF, buffor, size);
write(plikT,buffor,size);
free(buffor);
   }
buffor = malloc(size);
read(plikF, buffor,size);
write(plikT,buffor,size);
free(buffor);
}
close(plikF);
close(plikT);
return 1;
}

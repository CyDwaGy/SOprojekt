#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ftw.h>

#include "Filip.h"
#include "mateusz.h"

#define G 1073741824
#define M 1048576
#define K 1024

static volatile sig_atomic_t sig = 0;// zmienna do sprawdzania czy zostal wyslany sigusr1

void sig_handler_sigusr1(int signum){
  sig=signum;
}

int toSleep(int time){
  if(time<0)
    return -1;
  sig=0;
  signal(SIGUSR1,sig_handler_sigusr1); // zarejestrowanie Sygnalu
  printf("Sleep\n");
  sleep(time);
  if(sig!=0)
    return 1;
  else
    return 2;
}

int tryDelete(char * source,char * destiny)//linux nie pozwala na katalog i plik o tej samej nazwie w jednym miejscu
{
  if(CheckIfKatalog(destiny)==-1)return 0;
  if(CheckIfKatalog(source)==-1) 
  {
    if(remove(destiny)==-1)
      return -1;
    else return 1;
  }
  return 0;
}

unsigned long long int sizeToULLI(char * string){
	int size=strlen(string);
	if(size<1) return -1;
	if(string[size-1]=='G')
		return strtoull(string,NULL,0) * G;
	else if(string[size-1]=='M')
		return strtoull(string,NULL,0) * M;
	else if(string[size-1]=='K')
		return strtoull(string,NULL,0) * K;
	else
		return strtoull(string,NULL,0);
}

int unlink_cb(const char * fpath,const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	int rv = remove(fpath);
	if(rv)
		perror(fpath);
	return rv;
}

int delDir(char * path)
{
	return nftw(path, unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}


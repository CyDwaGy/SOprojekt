#include "marcin.h"
#include "mateusz.h"
#include "Filip.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#define buf_size 8192

long long int CheckSize(char * fd){
  struct stat buf;
  stat(fd, &buf);
  long long int size=buf.st_size;
  return size;
}


int CopyMaly(char*pathF, char* pathT)
{
//        char *  buffor = (char *) malloc(buf_size);
	char buffor[buf_size];
        int plikF = open(pathF, O_RDONLY);
	if (plikF<0)
		return -1;
        int plikT = open(pathT, O_CREAT|O_WRONLY,0666);
	if(plikT<0)
		return -1;
	ssize_t nread;
	while(nread = read(plikF,buffor,sizeof buffor), nread>0)
	{
		char * out=buffor;
		ssize_t nwritten;
		do{
			nwritten = write(plikT, out, nread);
			if(nwritten >=0)
			{
				nread -= nwritten;
				out += nwritten;
			}
		}while(nread > 0);
	}
//	free(buffor);
        close(plikF);
        close(plikT);
        return 1;
}


int CopyDuzy(char * pathF,char * pathT)
{
	int fileF = open(pathF, O_RDWR);
	if(fileF<0)
		return -1;
	struct stat statbuf;
	fstat(fileF, &statbuf);
	char * map  = mmap(NULL, statbuf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fileF,0);
	if(map == MAP_FAILED){
		printf("Maping failed\n");
		return -1;
	}
	close(fileF);
	int fileT = open(pathT, O_CREAT|O_WRONLY,0666);
	if(fileT<0)
		return -1;
	long int size=statbuf.st_size;
	ssize_t n=0;
	do{
		n = write(fileT,map=map+n,size-=n);
	}while(size>0);
	close(fileT);
	return 0;
}

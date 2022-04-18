#include "marcin.h"
#include "mateusz.h"
#include "Filip.h"
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define buf_size 4096

long long int CheckSize(char * fd){
  struct stat buf;
  stat(fd, &buf);
  int size=buf.st_size;
  return size;
}
int main(int args, char ** argv)
{
	char * pathF = argv[1];
	char * pathT = argv[2];
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
	int fileT = open(pathT, O_CREAT|O_WRONLY| O_EXCL,0666);
	ssize_t n = write(fileT,map,statbuf.st_size);//tu trzeba do whila zrobic poniewarz max jaki moze zapisac write to 2gb 
	if(n != statbuf.st_size){
		printf("Write failed\nn=%ld\nstatbuf=%ld\n",n,statbuf.st_size);
		return -1;
	}
	return 0;
}

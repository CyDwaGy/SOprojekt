#include "marcin.h"
#include "mateusz.h"
#include "Filip.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define buf_size 8192

long long int CheckSize(char * fd){
  struct stat buf;
  stat(fd, &buf);
  int size=buf.st_size;
  return size;
}
/*
int CopyMaly(char*pathF, char* pathT)
{
        unsigned char * buffor;
        int plikF = open(pathF, O_RDONLY);
        int plikT = open(pathT, O_CREAT|O_WRONLY);
        long long int size=CheckSize(pathF);
        struct stat st;
        stat(pathF, &st);
        chmod(pathT, st.st_mode);
        if(size<buf_size){
                buffor =  malloc(size);
                read(plikF,buffor,size);
                write(plikT,buffor,size);
                free(buffor);
        }
        else
        {
                buffor = malloc(buf_size);
                while(size>=buf_size)
                {
                        size-=buf_size;
                        read(plikF, buffor,buf_size);
                        write(plikT,buffor,buf_size);
                }
                free(buffor);
		if(size>0)
		{
        	        buffor = malloc(size);
	                read(plikF, buffor,size);
	                write(plikT,buffor,size);
                	free(buffor);
		}
        }
        close(plikF);
        close(plikT);
        return 1;
}
*/


int CopyMaly(char*pathF, char* pathT)
{
//        char *  buffor = (char *) malloc(buf_size);
	char buffor[buf_size];
        int plikF = open(pathF, O_RDONLY);
	if (plikF<0)
		return -1;
        int plikT = open(pathT, O_CREAT|O_WRONLY| O_EXCL,0666);
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



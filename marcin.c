#include "marcin.h"
#include "mateusz.h"
#include "Filip.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#define buf_size 16384

long long int CheckSize(char * fd){
  struct stat buf;
  stat(fd, &buf);
  int size=buf.st_size;
  return size;
}
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



#include "gn.h"
#include "marcin.h"
#include "mateusz.h"
#include "Filip.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <dirent.h>
#include <string.h>

int Copy(char*pathF, char* pathT, unsigned long long int size){
    int ret;
    if (CheckSize(pathF) > size){
        ret = CopyDuzy(pathF, pathT);
    }
    else{
        ret = CopyMaly(pathF, pathT);
    }
    //log jesli ret=-1 albo 0
    return ret;
}

int DelDir(char*pathF, char* pathT, int recurrence){
    DIR *d;
    struct dirent *dir;
    d = opendir(pathT);
    int x;
    char tmpF[10000], tmpT[10000];
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name,"." )) || (!strcmp(dir->d_name,".." )))){
                sprintf(tmpT, "%s/%s", pathT, dir->d_name);
                sprintf(tmpF, "%s/%s", pathF, dir->d_name);
                x = CheckIfExist(tmpF);
                    if (x == 0)
                        delDir(tmpT);
                    else if (x==1){
                        if (CheckIfKatalog(tmpT)){
                            if (recurrence == 1){
                                DelDir(tmpF,tmpT,1);
                            }
                        }
            }
        }
    }
    }
    return 0;
}

int CopyDir(char*pathF, char* pathT, int recurrence, unsigned long long int size){
    printf("%s, %s",pathF,pathT);
    DIR *d;
    struct dirent *dir;
    d = opendir(pathF);
    char tmpF[10000], tmpT[10000];
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name,"." )) || (!strcmp(dir->d_name,".." )))){ // nie zaczytujemy '.' i '..'
            printf("\n%s ", dir->d_name);
            sprintf(tmpT, "%s/%s", pathT, dir->d_name);
            sprintf(tmpF, "%s/%s", pathF, dir->d_name);
		if (CheckIfKatalog(tmpF)) {
                printf("%s", "Katalog");
                if (recurrence == 1) {
                    printf("\n\n rekurencja \n\n");
		    printf("%d\n",CheckIfKatalog(tmpF));
		    if(CheckIfKatalog(tmpT)==-1)
			{
				mkdir(tmpT,0777);
			}
                   CopyDir(tmpF, tmpT, 1, size);

                }
            }
            else
		{
                	printf("%s", "plik");
            		Copy(tmpF, tmpT, size);
		}
        }
        }
        closedir(d);
    }
    return 0;
}

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

int Copy(char*pathF, char* pathT, long long int size){
    int ret;
    if (CheckSize(pathF) > size){
        ret = CopyDuzy(pathF, pathT);
    }
    else{
        ret = CopyMaly(pathF, pathT);
    }
    //log jesli ret=-1
    return ret;
}

int CopyDir(char*pathF, char* pathT, int recurrence, long long int size){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name,"." )) || (!strcmp(dir->d_name,".." )))){ // nie zaczytujemy '.' i '..'
            printf("\n%s ", dir->d_name);
            if (CheckIfKatalog(dir->d_name))
                printf("%s", "Katalog");
                if (recurrence == 1){
                    char tmpF[200], tmpT[200];
                    sprintf|(tmpF,"%s/%s",pathF,dir->d_name);
                    sprintf|(tmpT,"%s/%s",pathT,dir->d_name);
                    printf("\n\n%s %s \n\n",tmpF,tmpT);
                }
            else
                printf("%s", "plik");
        }
        }
        closedir(d);


    }
    return 0;
}
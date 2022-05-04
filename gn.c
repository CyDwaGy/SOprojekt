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
#include <syslog.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>

void Log(char *log) {
    openlog("SyncMain", LOG_PID, LOG_USER);
    syslog(LOG_INFO, "%s",log);
    closelog();
}

int Copy(char *pathF, char *pathT, unsigned long long int size) {
    int ret;
    char tmp[11000];
    struct stat foo;
    time_t mtime;
    struct utimbuf new_times;
    if (CheckSize(pathF) > size) {
        ret = CopyDuzy(pathF, pathT);
    } else {
        ret = CopyMaly(pathF, pathT);
    }
    if(ret==1){
    sprintf(tmp, "Skopiowano plik %s do %s", pathF, pathT);
    stat(pathF, &foo);
    mtime = foo.st_mtime; /* seconds since the epoch */
    new_times.actime = foo.st_atime; /* keep atime unchanged */
    new_times.modtime = foo.st_mtime;    /* set mtime to current time */
    utime(pathT, &new_times);
}
    else{
	sprintf(tmp, "Nieudane kopiowanie plik %s do %s", pathF, pathT);
	}

    Log(tmp);
    return ret;
}

int DelDir(char *pathF, char *pathT, int recurrence) {
    DIR *d;
    struct dirent *dir;
    d = opendir(pathT);
    int x;
    struct stat st;
    char tmpF[10000], tmpT[10000], tmp[11000];
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name, ".")) || (!strcmp(dir->d_name, "..")))) {
                sprintf(tmpT, "%s/%s", pathT, dir->d_name);
                sprintf(tmpF, "%s/%s", pathF, dir->d_name);
                x = CheckIfExist(tmpF);
                if((dir->d_type==8 ||dir->d_type==4) &&x == 0) {
                    delDir(tmpT);
                    sprintf(tmp, "Usunięto plik %s", tmpT);
                    Log(tmp);
                } else if (x == 1) {
                    if (CheckIfKatalog(tmpF)==1) {
                        if (recurrence == 1) {
                            DelDir(tmpF, tmpT, 1);
                        }
                    }
                }
            }
        }
    }
    closedir(d);
    return 0;
}

int CopyDir(char *pathF, char *pathT, int recurrence, unsigned long long int size) {
    DIR *d;
    struct dirent *dir;
    d = opendir(pathF);
    char tmpF[10000], tmpT[10000];
    struct stat st;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name, ".")) || (!strcmp(dir->d_name, "..")))) { // nie zaczytujemy '.' i '..'
		lstat(dir->d_name, &st);
                sprintf(tmpT, "%s/%s", pathT, dir->d_name);
                sprintf(tmpF, "%s/%s", pathF, dir->d_name);
                if (CheckIfKatalog(tmpF)==1) {
                    if (recurrence == 1) {
                        if (CheckIfExist(tmpT) == 0) {
                            mkdir(tmpT, 0700);
                        }
                        CopyDir(tmpF, tmpT, 1, size);
                    }
                } else {
		printf("\n %s, %d \n",dir->d_name, dir->d_type);
		printf("\n %s %s, %d \n",tmpF,tmpT,CheckDateDiff(tmpF,tmpT));

                    if (CheckDateDiff(tmpF, tmpT)==1 || CheckIfExist(tmpT)==0)
	                if(dir->d_type==8 ||dir->d_type==4) {
                            Copy(tmpF, tmpT, size);}
                }
            }
        }
        closedir(d);
    }
    return 0;
}

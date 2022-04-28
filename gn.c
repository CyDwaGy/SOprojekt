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
    syslog(LOG_INFO, log);
    closelog();
}

int Copy(char *pathF, char *pathT, unsigned long long int size) {
    int ret;
    char tmp[100];
    struct stat foo;
    time_t mtime;
    struct utimbuf new_times;
    if (CheckSize(pathF) > size) {
        ret = CopyDuzy(pathF, pathT);
    } else {
        ret = CopyMaly(pathF, pathT);
    }
    sprintf(tmp, "Skopiowano plik %s do %s", pathF, pathT);

    stat(pathF, &foo);
    mtime = foo.st_mtime; /* seconds since the epoch */
    new_times.actime = foo.st_atime; /* keep atime unchanged */
    new_times.modtime = foo.st_mtime;    /* set mtime to current time */
    utime(pathT, &new_times);
    Log(tmp);
    return ret;
}

int DelDir(char *pathF, char *pathT, int recurrence) {
    DIR *d;
    struct dirent *dir;
    d = opendir(pathT);
    int x;
    char tmpF[10000], tmpT[10000], tmp[100];
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name, ".")) || (!strcmp(dir->d_name, "..")))) {
                sprintf(tmpT, "%s/%s", pathT, dir->d_name);
                sprintf(tmpF, "%s/%s", pathF, dir->d_name);
                x = CheckIfExist(tmpF);
                if (x == 0 && CheckIfRegular(tmpF)) {
                    delDir(tmpT);
                    sprintf(tmp, "Usunięto plik %s", tmpT);
                    Log(tmp);
                } else if (x == 1) {
                    if (CheckIfKatalog(tmpT)) {
                        if (recurrence == 1) {
                            DelDir(tmpF, tmpT, 1);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int CopyDir(char *pathF, char *pathT, int recurrence, unsigned long long int size) {
    DIR *d;
    struct dirent *dir;
    d = opendir(pathF);
    char tmpF[10000], tmpT[10000];
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (!((!strcmp(dir->d_name, ".")) || (!strcmp(dir->d_name, "..")))) { // nie zaczytujemy '.' i '..'
                sprintf(tmpT, "%s/%s", pathT, dir->d_name);
                sprintf(tmpF, "%s/%s", pathF, dir->d_name);
                if (CheckIfKatalog(tmpF)) {
                    if (recurrence == 1) {
                        if (CheckIfKatalog(tmpT) == -1) {
                            mkdir(tmpT, 0777);
                        }
                        CopyDir(tmpF, tmpT, 1, size);
                    }
                } else {
                    if (!CheckDateDiff(tmpF, tmpT) || !CheckIfExist(tmpT))
                        if(CheckIfRegular(tmpF))
                            Copy(tmpF, tmpT, size);
                }
            }
        }
        closedir(d);
    }
    return 0;
}

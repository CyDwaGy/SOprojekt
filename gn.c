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

int CopyDir(char*pathF, char* pathT, int recurrence){
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n ", dir->d_name);
            if (CheckIfKatalog(dir->d_name))
                printf("%s", "Katalog")
            else
                printf("%s", "plik")
        }
        closedir(d);
    }
    return 0;
}
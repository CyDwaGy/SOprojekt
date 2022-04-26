//
// Created by Filip on 05.04.2022.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "Filip.h"
int backslash(char ** path)
{
    char * tmp1 = *path;
    char tmp2[200];
    int length = strlen(tmp1);
    char slash = '\\';
    char ostatnia = tmp1[length-1];
    if(ostatnia != slash)
    {
        sprintf (tmp2, "%s\\", tmp1);
        asprintf (path, "%s", tmp2);
    }
}
int slash(char ** path)
{
    char * tmp1 = *path;
    char tmp2[200];
    int length = strlen(tmp1);
    char slash = '/';
    char ostatnia = tmp1[length-1];
    if(ostatnia != slash)
    {
        sprintf (tmp2, "%s/", tmp1);
        asprintf (path, "%s", tmp2);
    }
}
int CheckIfKatalog( char *path)
{
    struct stat type;
    if(stat(path, &type)!=0) return -1;
    if (S_ISDIR(type.st_mode) == 0) return 0;
    else return 1;
}
int CheckIfExist(char *path, char *plik)
{
    if(CheckIfKatalog(path)==-1)return -1;
    char buffer[200];
    sprintf (buffer, "%s%s", path, plik);
    if(CheckIfKatalog(buffer) == 0) return 1;
    else return 0;
}
int CheckDateDiff(char *path1, char *path2)
{
    if(CheckIfKatalog(path1) != 0) return -1;
    if(CheckIfKatalog(path2) != 0) return -1;
    struct stat time;
    stat(path1, &time);

    long long file1_time = time.st_mtime;
    //printf("Last modified time: %lld\n", file1_time);
    stat(path2, &time);
    long long file2_time = time.st_mtime;
    //printf("Last modified time: %lld\n", file2_time);
    if (file1_time == file2_time) return 1;
    else return 0;
}


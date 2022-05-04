//
// Created by Filip on 05.04.2022.
//
#define _GNU_SOURCE
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include "Filip.h"
int CheckIfKatalog( char *path)
{
    struct stat type;
    if(stat(path, &type)!=0) return -1;
    if (S_ISDIR(type.st_mode) == 1) return 1;
    else return 0;
}
int CheckIfRegular( char *path)
{
    struct stat type;
    if(stat(path, &type)!=0) return -1;
    if (S_ISREG(type.st_mode) == 1) return 1;
    else return 0;
}
int CheckIfExist(char *path)
{
    if( access( path, F_OK ) != -1)
    {
	return 1;
    }
    else
    {
	return 0;
    }
    return -1;

}
int CheckIfLink(char *path)
{
    struct stat type;
    if(stat(path, &type)!=0) return -1;
    if (S_ISLNK(type.st_mode) == 1) return 1;
    else return 0;

}

int CheckDateDiff(char *path1, char *path2)
{
    if(CheckIfKatalog(path1) != 0) return -1;
    if(CheckIfKatalog(path2) != 0) return -1;
    struct stat time;
    struct stat time2;
    stat(path1, &time);
    stat(path2, &time2);
    if(difftime(time.st_mtime,time2.st_mtime)==0.0) return 0;
    else return 1;
}


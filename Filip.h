#ifndef FILIP_H_
#define FILIP_H_

int slash(char ** path);
int backslash(char ** path);
int CheckIfKatalog( char *path);
int CheckIfExist(char *path);
int CheckIfLink(char *path);
int CheckDateDiff(char *path1, char *path2);
int CheckIfRegular( char *path);
#endif 

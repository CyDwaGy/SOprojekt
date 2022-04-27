#ifndef MATEUSZ_H_
#define MATEUSZ_H_

int toSleep(int time);
int tryDelete(char * source,char * destiny);
unsigned long long int sizeToULLI(char * string);
int unlink_cb(const char * fpath,const struct stat *sb, int typeflag, struct FTW *ftwbuf);
int delDir(char * path);

#endif

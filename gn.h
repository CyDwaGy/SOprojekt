#ifndef SOPROJEKT_GN_H
#define SOPROJEKT_GN_H
int CopyDir(char*pathF, char* pathT, int recurrence,unsigned long long int size);
int Copy(char*pathF, char* pathT,unsigned long long int size);
int DelDir(char*pathF, char* pathT, int recurrence);
void Log(char * log);

#endif

#include "Filip.h"
#include "marcin.h"
#include "gn.h"
#include "mateusz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _1G 1073741824
#define _1M 1048576
#define _1K 1024
int main(int arc,char * argv[]){
	int T = 300;
	int R = 0;
	unsigned long long int S = _1G;
	char * source=argv[1];
	char * destiny=argv[2];
	if(CheckIfKatalog(source)==1)
		printf("%s jest katalogiem\n",source);
	else{
		printf("%s jest bledne\n",source);
		return -1;
	}
	if(CheckIfKatalog(destiny)==1)
		printf("%s jest katalogiem\n",destiny);
	else{
		printf("%s jest bledne\n",destiny);
		return -1;
	}
	int i;
	for(i=3; i<arc;i++){
		if(strcmp(argv[i],"-T")==0){
			if(i+1>=arc){
				printf("Blad parametrow\n");
				return -1;
			}
			T = atoi(argv[++i]);
		}
		else if(strcmp(argv[i],"-R")==0)
			R=1;
		else if(strcmp(argv[i],"-S")==0){
			if(i+1>=arc){
				printf("Blad parametrow\n");
				return -1;
			}
			S=sizeToULLI(argv[++i]);
		}
	}
	printf("Parametr S to %llu\n",S);
	printf("Parametr T to %d\n",T);
	printf("Parametr R to %d\n",R);
	int a;
	char tmp[100];
    while(1)
   {
	printf("Synchronizacja\n");
        DelDir(source, destiny, R);
        CopyDir(source,destiny,R,S);
	printf("Sen\n");
        a=toSleep(T);
	if(a==2){
		sprintf(tmp, "Budzenie po %ds", T);
                Log(tmp);
		printf("Budzenie po %ds\n",T);
	}
	else if (a==1)
	{
		sprintf(tmp,"Budzenie po Siguser1");
                Log(tmp);
		printf("Budzenie po Siguser1\n");
	}
	else
		printf("Blad");
    }
	return 0;
}

=#include <sys/stat.h>

struct stat results;

int main()
{
    if (stat("xd.txt", &results) == 0)
        printf("File size: %d\n", results.st_size);
    else
        printf("Blad.\n");

    return 0;
}


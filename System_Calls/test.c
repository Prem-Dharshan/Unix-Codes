#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>


int main(int argc, char argv[]) {
    
    int fd1, fd2;
    char ch;

    if (argc != 3) {
        printf("Args error");
        return 1;
    }

    fd1 = open(argv[1], O_RDONLY);

    if (fd1 < 0) {
        perror('sd');
    }

    fd2 = creat(argv[2], 0777);

    if (fd2 < 0) {
        perror("sd");
    }

    


    return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main( )
{ 
    printf("Files in Directory are:\n");
    system("ls -l");

    return 0;
}

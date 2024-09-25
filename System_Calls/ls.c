#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    struct dirent *dptr;  // Pointer to directory entry structure
    char buff[100];
    DIR *dirp;  // Directory pointer

    printf("Enter directory name: ");
    scanf("%s", buff);

    // Attempt to open the specified directory
    if ((dirp = opendir(buff)) == NULL) {
        printf("The given directory does not exist or cannot be opened.\n");
        exit(1);
    }

    printf("Contents of the directory '%s':\n", buff);
    
    // Read the directory contents
    while ((dptr = readdir(dirp)) != NULL) {
        printf("%s\n", dptr->d_name);
    }

    // Close the directory after reading
    closedir(dirp);

    return 0;
}

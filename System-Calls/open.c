#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Open the file "example.txt" with read and write permissions, create if it doesn't exist
    fd = open("./sample/example.txt", O_RDWR | O_CREAT);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    printf("File opened successfully with file descriptor: %d\n", fd);

    // Close the file
    if (close(fd) == -1) {
        perror("Error closing file");
        return 1;
    }

    printf("File closed successfully\n");

    return 0;
}
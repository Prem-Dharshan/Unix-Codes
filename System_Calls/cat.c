#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd, i;
    char buf[2];

    // Ensure that the program is called with a file as argument
    if (argc != 2) {
        printf("Usage: %s <file_to_read>\n", argv[0]);
        return 1;
    }

    // Open the file in read-only mode
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("File open error");  // Display error if file cannot be opened
        return 1;
    }

    // Read and print the file contents byte by byte
    while ((i = read(fd, buf, 1)) > 0) {
        printf("%c", buf[0]);
    }

    // Close the file descriptor
    close(fd);

    return 0;
}

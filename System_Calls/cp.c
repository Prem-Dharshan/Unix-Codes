#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd1, fd2;
    char buf[1];  // Buffer to read 1 byte at a time

    // Ensure there are exactly 2 arguments (file1 and file2)
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    // Open the source file for reading
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0) {
        perror("Error opening source file");
        return 1;
    }

    // Create the destination file (or truncate if it exists)
    fd2 = creat(argv[2], 0777);
    if (fd2 < 0) {
        perror("Error creating destination file");
        close(fd1);  // Close the source file before exiting
        return 1;
    }

    // Read from the source file and write to the destination file
    while (read(fd1, buf, 1) > 0) {
        write(fd2, buf, 1);
    }

    // Remove the source file
    remove(argv[1]);

    // Close both files
    close(fd1);
    close(fd2);

    printf("File copied and source file removed successfully.\n");

    return 0;
}

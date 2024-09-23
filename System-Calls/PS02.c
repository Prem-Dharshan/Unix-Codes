// Write a program that opens a file (with the open() system call) and then calls fork() to create a new process.
// Can both the child and parent access the file descriptor returned by open()?
// What happens when they are writing to the file concurrently, i.e., at the same time?

#include <stdio.h>  // For Standard Input/Output
#include <unistd.h> // For System Calls
#include <fcntl.h>  // For file handling
#include <string.h> // For string handling

int main() {

    int fd_open, fd_read;

    fd_open = open("./sample/example.txt", O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0644);
    if (fd_open == -1) {
        perror("Error opening file");
        return 1;
    }

    fd_read = open("./sample/example.txt", O_RDONLY);
    if (fd_read == -1) {
        perror("Error opening file");
        return 1;
    }

    int pid = fork();  // Create a new process

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("In Child process...\n");

        // Read the file
        printf("Reading the file with fd %d\n", fd_read);
        char buffer[1024];
        int bytes_read = read(fd_read, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("Error reading file");
            return 1;
        }
        printf("Read %d bytes from the file: %s\n", bytes_read, buffer);

        printf("Writing to the file with fd %d\n", fd_open);
        const char *child_msg = "This is the child process writing.\n";
        write(fd_open, child_msg, strlen(child_msg));
        printf("Child process finished writing.\n");
    } 
    else {
        // Parent process
        printf("In Parent process...\n");

        // Read the file
        printf("Reading the file with fd %d\n", fd_read);
        char buffer[1024];
        int bytes_read = read(fd_read, buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("Error reading file");
            return 1;
        }
        printf("Read %d bytes from the file: %s\n", bytes_read, buffer);

        printf("Writing to the file with fd %d\n", fd_open);
        const char *parent_msg = "This is the parent process writing.\n";
        write(fd_open, parent_msg, strlen(parent_msg));
        printf("Parent process finished writing.\n");
    }

    // Close the file
    if (close(fd_open) == -1) {
        perror("Error closing file");
        return 1;
    }

    if (close(fd_read) == -1) {
        perror("Error closing file");
        return 1;
    }

    printf("File closed successfully\n");

    return 0;
}

// Both the child and parent can access the file descriptor returned by open().
// When they are writing to the file concurrently, the writes are interleaved.
// This is because the child and parent processes are running concurrently and the operating system scheduler decides when to switch between them.
// So, the writes from the child and parent processes are interleaved in the file.
// The order of writes depends on the scheduler and the timing of the context switches between the processes.
// The writes may not be in the order in which they were executed in the program.
// The writes may also be split into smaller chunks and interleaved with writes from the other process.

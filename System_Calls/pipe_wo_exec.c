#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int fd[2];  // Array to hold the two ends of the pipe: fd[0] is for reading, fd[1] is for writing
    pid_t pid;
    char write_msg[BUFFER_SIZE] = "Hello from the parent process!";
    char read_msg[BUFFER_SIZE];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork the process to create a child
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        close(fd[1]);  // Close the write end of the pipe in the child process

        // Read from the pipe
        read(fd[0], read_msg, BUFFER_SIZE);
        printf("Child process received: %s\n", read_msg);

        close(fd[0]);  // Close the read end after reading
    }
    else {
        // Parent process
        close(fd[0]);  // Close the read end of the pipe in the parent process

        // Write to the pipe
        write(fd[1], write_msg, strlen(write_msg) + 1);  // +1 to include the null terminator
        printf("Parent process sent: %s\n", write_msg);

        close(fd[1]);  // Close the write end after writing
        wait(NULL);    // Wait for the child process to finish
    }

    return 0;
}

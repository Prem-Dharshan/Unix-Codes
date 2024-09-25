#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2];  // Pipe 1: Parent writes, Child reads
    int pipe2[2];  // Pipe 2: Child writes, Parent reads
    pid_t pid;
    char parent_msg[BUFFER_SIZE] = "Hello from Parent!";
    char child_msg[BUFFER_SIZE] = "Hello from Child!";
    char read_buffer[BUFFER_SIZE];

    // Create pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork to create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process

        // Close unused ends of the pipes
        close(pipe1[1]);  // Close the write end of pipe 1 (Parent -> Child)
        close(pipe2[0]);  // Close the read end of pipe 2 (Child -> Parent)

        // Read from the parent
        read(pipe1[0], read_buffer, BUFFER_SIZE);
        printf("Child process received: %s\n", read_buffer);

        // Write a message to the parent
        write(pipe2[1], child_msg, strlen(child_msg) + 1);
        printf("Child process sent: %s\n", child_msg);

        // Close the pipes
        close(pipe1[0]);  // Close read end after reading
        close(pipe2[1]);  // Close write end after writing
    }
    else {
        // Parent process

        // Close unused ends of the pipes
        close(pipe1[0]);  // Close the read end of pipe 1 (Parent -> Child)
        close(pipe2[1]);  // Close the write end of pipe 2 (Child -> Parent)

        // Write a message to the child
        write(pipe1[1], parent_msg, strlen(parent_msg) + 1);
        printf("Parent process sent: %s\n", parent_msg);

        // Read the response from the child
        read(pipe2[0], read_buffer, BUFFER_SIZE);
        printf("Parent process received: %s\n", read_buffer);

        // Close the pipes
        close(pipe1[1]);  // Close write end after writing
        close(pipe2[0]);  // Close read end after reading

        wait(NULL);  // Wait for the child process to finish
    }

    return 0;
}

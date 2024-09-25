#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int pipe1[2], pipe2[2];  // Two pipes: pipe1 for Child1 -> Child2, pipe2 for Child2 -> Child1
    pid_t pid1, pid2;
    char child1_msg[BUFFER_SIZE] = "Hello from Child Process 1!";
    char child2_msg[BUFFER_SIZE] = "Hello from Child Process 2!";
    char read_buffer[BUFFER_SIZE];

    // Create the two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // Fork first child
    pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }
    
    if (pid1 == 0) {
        // Child Process 1
        
        // Close the unused ends of the pipes
        close(pipe1[0]);  // Close read end of pipe 1 (since this child is writing to it)
        close(pipe2[1]);  // Close write end of pipe 2 (since this child is reading from it)

        // Write message to Child 2 using pipe1
        write(pipe1[1], child1_msg, strlen(child1_msg) + 1);  // +1 for null terminator
        printf("Child 1: Sent message to Child 2: %s\n", child1_msg);

        // Read message from Child 2 using pipe2
        read(pipe2[0], read_buffer, BUFFER_SIZE);
        printf("Child 1: Received message from Child 2: %s\n", read_buffer);

        // Close the remaining pipe ends
        close(pipe1[1]);
        close(pipe2[0]);

        exit(0);
    }

    // Fork second child
    pid2 = fork();

    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Child Process 2
        
        // Close the unused ends of the pipes
        close(pipe1[1]);  // Close write end of pipe 1 (since this child is reading from it)
        close(pipe2[0]);  // Close read end of pipe 2 (since this child is writing to it)

        // Read message from Child 1 using pipe1
        read(pipe1[0], read_buffer, BUFFER_SIZE);
        printf("Child 2: Received message from Child 1: %s\n", read_buffer);

        // Write message to Child 1 using pipe2
        write(pipe2[1], child2_msg, strlen(child2_msg) + 1);  // +1 for null terminator
        printf("Child 2: Sent message to Child 1: %s\n", child2_msg);

        // Close the remaining pipe ends
        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);
    }

    // Parent process
    // Close all pipe ends in the parent process since it's not involved in communication
    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    // Wait for both children to finish
    wait(NULL);  // Wait for Child 1
    wait(NULL);  // Wait for Child 2

    printf("Parent: Both child processes have finished.\n");

    return 0;
}

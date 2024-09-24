#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        sleep(2); // Simulate some work in the child process
        printf("Child process exiting\n");
        exit(0);
    }
    else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Waiting for child process to finish...\n");
        wait(NULL); // Wait for the child process to finish
        printf("Child process finished\n");
    }

    return 0;
}
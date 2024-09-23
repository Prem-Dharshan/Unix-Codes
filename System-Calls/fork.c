#include <stdio.h>  // For Standard Input/Output
#include <unistd.h> // For System Calls

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Hello from the child process!\n");
    } else {
        // Parent process
        printf("Hello from the parent process!\n");
    }

    return 0;
}
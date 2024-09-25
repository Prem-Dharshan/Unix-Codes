#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int numProcesses, i;
    pid_t pid;

    // Ask the user how many processes to create
    printf("Enter the number of child processes to create: ");
    scanf("%d", &numProcesses);

    // Create child processes based on user input
    for (i = 0; i < numProcesses; i++) {
        pid = fork();  // Create a new child process

        if (pid < 0) {
            // Fork failed
            perror("Fork failed");
            exit(1);
        } 
        else if (pid == 0) {
            // Child process
            printf("Child process %d: PID = %d, Parent PID = %d\n", i + 1, getpid(), getppid());
            exit(0);  // Exit the child process after it finishes its work
        } 
        else {
            // Parent process (wait for the child to finish)
            wait(NULL);  // Wait for the current child process to finish
        }
    }

    // Parent process exits after all child processes are done
    printf("All child processes have finished.\n");

    return 0;
}

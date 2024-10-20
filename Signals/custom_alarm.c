#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void alarm_handler(int signum);

int main() {
    int pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child process
        printf("Child: Alarm Signal Handler Registered.\n");

        // Register signal handler for SIGALRM in the child
        signal(SIGALRM, alarm_handler);

        // Keep the child alive and waiting for signals indefinitely
        for(;;);  // Infinite loop
    }
    else {  // Parent process
        sleep(5);  // Delay before sending the first signal

        for (int i = 1; i <= 5; i++) {
            printf("Parent: Sending alarm %d to child.\n", i);

            // Send SIGALRM signal to the child
            kill(pid, SIGALRM);

            // Sleep for 2 seconds before sending the next alarm
            sleep(2);
        }

        printf("Parent: 5 Alarms sent, killing the child process.\n");

        // After sending 5 alarms, terminate the child process
        kill(pid, SIGKILL);
    }

    return 0;
}

void alarm_handler(int signum) {
    printf("Child: Received SIGALRM signal (%d).\n", signum);
}

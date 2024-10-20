#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler function for SIGALRM
void alarm_handler(int signum) {
    printf("Alarm triggered! Signal number: %d\n", signum);
}

int main() {
    // Register signal handler for SIGALRM
    signal(SIGALRM, alarm_handler);

    printf("Setting alarm for 5 seconds.\n");

    // Set an alarm for 5 seconds
    alarm(5);

    // The process will sleep, waiting for the alarm signal
    printf("Waiting for the alarm...\n");

    // Pause the program until a signal is received
    pause();

    printf("Program execution resumes after alarm.\n");

    return 0;
}

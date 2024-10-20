#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sighup(int signum);
void sigint(int signum);
void sigquit(int signum);

int main()
{
    int pid;

    pid = fork();
    if (pid == 0) // Child process
    {
        printf("child\n");
        signal(SIGHUP, sighup);   // Set handler for SIGHUP
        signal(SIGINT, sigint);   // Set handler for SIGINT
        signal(SIGQUIT, sigquit); // Set handler for SIGQUIT
        for (;;); // Infinite loop
    }
    else // Parent process
    {
        sleep(3);

        printf("\nPARENT: sending SIGHUP\n\n");
        kill(pid, SIGHUP); // Send SIGHUP to child
        sleep(3);
        
        printf("\nPARENT: sending SIGINT\n\n");
        kill(pid, SIGINT); // Send SIGINT to child
        sleep(3);
        
        printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid, SIGQUIT); // Send SIGQUIT to child
        sleep(3);
    }
}

void sighup(int signum)
{
    signal(SIGHUP, sighup); // Reset SIGHUP handler
    printf("CHILD: I have received a SIGHUP\n");
}

void sigint(int signum)
{
    signal(SIGINT, sigint); // Reset SIGINT handler
    printf("CHILD: I have received a SIGINT\n");
}

void sigquit(int signum)
{
    printf("My parent has Killed me!!!\n");
    exit(0); // Terminate the child process
}

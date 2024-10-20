#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

#define NUM_CHILDREN 5
#define FILE_NAME "pids.txt"

sem_t *sem;

void child_process(int id) {
    char buffer[50];
    sprintf(buffer, "Child PID: %d\n", getpid());

    sem_wait(sem); // Wait for semaphore

    // Write PID to file
    int fd = open(FILE_NAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    write(fd, buffer, strlen(buffer));
    close(fd);

    sem_post(sem); // Signal semaphore
    exit(0); // Exit child process
}

int main() {
    sem = sem_open("/pidsem", O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    printf("Parent PID: %d\n", getpid());

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            child_process(i);
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
    }

    // Wait for all child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    // Read and print PID file contents
    printf("PIDs written to %s:\n", FILE_NAME);
    char line[100];
    FILE *file = fopen(FILE_NAME, "r");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);

    // Clean up
    sem_close(sem);
    sem_unlink("/pidsem");
    return 0;
}

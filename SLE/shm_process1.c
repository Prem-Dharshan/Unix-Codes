// shm_process1.c (Reader)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key = ftok("shmfile", 65); // Create a unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Create shared memory segment
    char *str = (char*) shmat(shmid, (void*)0, 0); // Attach to the segment

    printf("Reader Process: Reading from shared memory...\n");
    while (1) {
        if (strlen(str) > 0) {
            printf("Received from shared memory: %s\n", str);
            memset(str, 0, SHM_SIZE); // Clear the memory after reading
        }
        sleep(1); // Read every second
    }

    shmdt(str); // Detach from shared memory
    shmctl(shmid, IPC_RMID, NULL); // Destroy the shared memory
    return 0;
}

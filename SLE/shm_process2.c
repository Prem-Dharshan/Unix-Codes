// shm_process2.c (Writer 1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Shared memory size

int main() {
    key_t key = ftok("shmfile", 65); // Create a unique key
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT); // Get shared memory segment
    char *str = (char*) shmat(shmid, (void*)0, 0); // Attach to the segment

    for (int i = 0; i < 5; i++) {
        sprintf(str, "Message from Process 2: %d", i + 1);
        sleep(2); // Write every 2 seconds
    }

    shmdt(str); // Detach from shared memory
    return 0;
}

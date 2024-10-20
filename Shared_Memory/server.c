#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SIZE 100

int main() 
{
    key_t shm_key = ftok(".", 1);
    int shm_id;
    char *shm_addr;

    shm_id = shmget(shm_key, SIZE, IPC_CREAT | 0666); // Use the generated key

    if (shm_id < 0) {
        perror("Can't create Shared memory");
        exit(1);
    }

    shm_addr = (char *)shmat(shm_id, NULL, 0);

    if (shm_addr == (char *)-1 ) {
        perror("Can't attach Shared memory");
        exit(1);
    }

    // Write characters to shared memory
    char *shm_ptr = shm_addr;
    for (char c = 'a'; c <= 'z'; c++) {
        *shm_ptr = c;
        shm_ptr++;
    }
    *shm_ptr = '\0'; // Null terminate the string

    // Indicate to the client that writing is done
    // *shm_addr = '1'; // Use '1' to signal

    printf("Server: Data written to shared memory.\n");

    // Wait for a signal from the client to exit
    while (*shm_addr != '*') {
        sleep(1);
    }

    printf("Server: Detaching shared memory...\n");
    shmdt(shm_addr);
    shmctl(shm_id, IPC_RMID, NULL); // Remove the shared memory segment

    return 0;
}

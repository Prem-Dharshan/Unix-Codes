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

    shm_id = shmget(shm_key, SIZE, 0666); // Use the same key as the server

    if (shm_id < 0) {
        perror("Can't access Shared memory");
        exit(1);
    }

    shm_addr = (char *)shmat(shm_id, NULL, 0);

    if (shm_addr == (char *)-1) {
        perror("Can't attach Shared memory");
        exit(1);
    }

    // // Wait for server to write
    // while (*shm_addr != '1') { // Wait for the server to write
    //     sleep(1);
    // }

    printf("Client: Read from shared memory: %s\n", shm_addr);

    // Signal the server to detach
    *shm_addr = '*'; // Use '*' to signal

    printf("Client: Detaching shared memory...\n");
    shmdt(shm_addr);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

#define KEY 2001
#define SHM_SIZE 26

int main() {
    int pid, shm_id;
    int* shared_area;

    // Create shared memory segment
    shm_id = shmget(KEY, SHM_SIZE * sizeof(int), IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("shmget error");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    
    if (pid == 0) {
        // Child process
        sleep(4); // Wait for the parent to write

        int* shared_area = (int *)shmat(shm_id, NULL, 0);
        if (shared_area == (void*) -1) {
            perror("shmat error");
            exit(1);
        }

        for (int i = 0; i < SHM_SIZE; i++) {
            printf("%d\n", shared_area[i]);
        }        

        if (shmdt(shared_area) < 0) {
            perror("shmdt error");
            exit(1);
        }
        exit(0);
    } else {
        // Parent process
        int* shared_area = (int *)shmat(shm_id, NULL, 0);
        if (shared_area == (void*) -1) {
            perror("shmat error");
            exit(1);
        }

        for (int i = 0; i < SHM_SIZE; i++) {
            shared_area[i] = i; // Writing integers 0 to 25
        }        

        wait(NULL); // Wait for the child process to finish

        if (shmdt(shared_area) < 0) {
            perror("shmdt error");
            exit(1);
        }
        if (shmctl(shm_id, IPC_RMID, NULL) < 0) {
            perror("shmctl error");
            exit(1);
        }
        exit(0);    
    }
    return 0;
}

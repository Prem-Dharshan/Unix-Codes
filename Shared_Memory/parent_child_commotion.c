#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/wait.h>

int main() {
    int shm_id;
    char *shm_addr;
    char *shm_ptr;

    int n = 0;

    shm_id = shmget(IPC_PRIVATE, 100, IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    shm_addr = (char *)shmat(shm_id, NULL, 0);
    if (shm_addr == (char *) -1){
        perror("shmat");
        exit(1);
    }

    shm_ptr = shm_addr;

    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {

        for (n; n < 10; n++) {
            *shm_ptr = '0' + n;
            shm_ptr++;
            *shm_ptr = '\0';
            printf("Child: %s\n", shm_addr);
            sleep(1);
        }

        shmdt(shm_addr);
        exit(0);
    }
    else {

        shm_ptr = shm_addr;
        
        for (n; n < 10; n++) {
            *shm_ptr = '0' + n;
            shm_ptr++;
            *shm_ptr = '\0';
            printf("Parent: %s\n", shm_addr);
            sleep(1);
        }

        wait(NULL);
        printf("Parent: Detaching shared memory...\n");
        shmdt(shm_addr);
        shmctl(shm_id, IPC_RMID, NULL);
        return 0;
    }
}

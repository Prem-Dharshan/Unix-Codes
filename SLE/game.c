#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define MIN 0
#define MAX 1
#define POINTS_TO_WIN 5

int main() {
    int shm_c, shm_d, *c_val, *d_val;
    int score_c = 0, score_d = 0;
    pid_t pid_c, pid_d;

    srand(time(NULL));  // Initialize random seed

    // Create shared memory segments
    shm_c = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    shm_d = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    
    if (shm_c < 0 || shm_d < 0) {
        printf("Shared memory creation failed.\n");
        exit(1);
    }

    // Attach shared memory
    c_val = (int *)shmat(shm_c, NULL, 0);
    d_val = (int *)shmat(shm_d, NULL, 0);

    if (*c_val == -1 || *d_val == -1) {
        printf("Shared memory attachment failed.\n");
        exit(1);
    }

    // Create child processes C and D
    if ((pid_c = fork()) == 0) {
        while (1) {
            *c_val = rand() % 100 + 1;  // C generates a random number
            sleep(1);
        }
        exit(0);
    }

    if ((pid_d = fork()) == 0) {
        while (1) {
            *d_val = rand() % 100 + 1;  // D generates a random number
            sleep(1);
        }
        exit(0);
    }

    // Parent process P
    while (1) {
        int flag = rand() % 2;  // Randomly choose MIN or MAX
        sleep(2);  // Simulate some delay
        
        printf("Parent received: C = %d, D = %d\n", *c_val, *d_val);
        
        if (*c_val == *d_val) {
            printf("Tie, no points awarded.\n");
            continue;  // Skip this round
        }

        if (flag == MIN) {
            printf("P chose MIN\n");
            if (*c_val < *d_val) {
                score_c++;
                printf("C wins this round. Score: C = %d, D = %d\n", score_c, score_d);
            } else {
                score_d++;
                printf("D wins this round. Score: C = %d, D = %d\n", score_c, score_d);
            }
        } else {
            printf("P chose MAX\n");
            if (*c_val > *d_val) {
                score_c++;
                printf("C wins this round. Score: C = %d, D = %d\n", score_c, score_d);
            } else {
                score_d++;
                printf("D wins this round. Score: C = %d, D = %d\n", score_c, score_d);
            }
        }

        // Check for win condition
        if (score_c == POINTS_TO_WIN) {
            printf("C wins the game!\n");
            break;
        }
        if (score_d == POINTS_TO_WIN) {
            printf("D wins the game!\n");
            break;
        }
    }

    // Cleanup
    kill(pid_c, SIGKILL);
    kill(pid_d, SIGKILL);
    shmdt(c_val);
    shmdt(d_val);
    shmctl(shm_c, IPC_RMID, NULL);
    shmctl(shm_d, IPC_RMID, NULL);

    return 0;
}

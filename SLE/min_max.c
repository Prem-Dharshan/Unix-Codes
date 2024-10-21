#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

int main() {
    int shm_id, *numbers, min_val, shm_min, shm_avg;
    float avg_val;

    // Create shared memory segment for 10 integers
    shm_id = shmget(IPC_PRIVATE, 10 * sizeof(int), IPC_CREAT | 0666);
    shm_min = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666);
    shm_avg = shmget(IPC_PRIVATE, sizeof(float), IPC_CREAT | 0666);

    if (shm_id < 0 || shm_min < 0 || shm_avg < 0) {
        printf("Shared memory creation failed.\n");
        exit(1);
    }

    // Attach shared memory
    numbers = (int *)shmat(shm_id, NULL, 0);
    int *min_result = (int *)shmat(shm_min, NULL, 0);
    float *avg_result = (float *)shmat(shm_avg, NULL, 0);

    // Initialize shared memory with random numbers
    srand(time(NULL));
    printf("Numbers: ");
    for (int i = 0; i < 10; i++) {
        numbers[i] = rand() % 100 + 1;
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Fork to create two child processes
    if (fork() == 0) {  // Child Process 1 - Find Minimum
        min_val = numbers[0];
        for (int i = 1; i < 10; i++) {
            if (numbers[i] < min_val) {
                min_val = numbers[i];
            }
        }
        *min_result = min_val;
        exit(0);
    }

    if (fork() == 0) {  // Child Process 2 - Calculate Average
        int sum = 0;
        for (int i = 0; i < 10; i++) {
            sum += numbers[i];
        }
        *avg_result = sum / 10.0;
        exit(0);
    }

    // Parent waits for both children to finish
    wait(NULL);
    wait(NULL);

    // Print results
    printf("Minimum: %d\n", *min_result);
    printf("Average: %.2f\n", *avg_result);

    // Detach and remove shared memory
    shmdt(numbers);
    shmdt(min_result);
    shmdt(avg_result);
    shmctl(shm_id, IPC_RMID, NULL);
    shmctl(shm_min, IPC_RMID, NULL);
    shmctl(shm_avg, IPC_RMID, NULL);

    return 0;
}

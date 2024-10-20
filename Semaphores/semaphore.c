#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *readCs(void *arg);
void *writeCs(void *arg);

char cs[40];
sem_t mutex;

int main() {
    
    sem_init(&mutex, 0, 1);  // Initialize semaphore
    printf("Semaphore initialized.\n");

    pthread_t t1, t2;

    const char *msg1 = "First Thread";
    const char *msg2 = "Second Thread";

    printf("Creating Threads\n");

    int t1_ret = pthread_create(&t1, NULL, writeCs, (void *) msg1);
    if (t1_ret != 0) {
        printf("Error creating write thread\n");
        return 1;
    } else {
        printf("Write thread created.\n");
    }

    int t2_ret = pthread_create(&t2, NULL, readCs, (void *) msg2);
    if (t2_ret != 0) {
        printf("Error creating read thread\n");
        return 1;
    } else {
        printf("Read thread created.\n");
    }

    // Wait for both threads to complete
    pthread_join(t1, NULL);
    printf("Write thread joined.\n");

    pthread_join(t2, NULL);
    printf("Read thread joined.\n");

    sem_destroy(&mutex);
    printf("Semaphore destroyed.\n");
    
    return 0;
}


void *readCs(void *arg) {
    printf("Reading CS...\n");
    sleep(1);  // Simulate waiting for write thread
    printf("Attempting to enter CS...\n");
    sem_wait(&mutex);
    printf("In CS (read)...\n");
    printf("Read content: %s\n", cs);
    sem_post(&mutex);
    printf("Exiting CS (read)...\n");
    pthread_exit(0);
}


void *writeCs(void *arg) {
    printf("Writing to CS...\n");
    printf("Attempting to enter CS...\n");
    sem_wait(&mutex);
    printf("In CS (write)...\n");
    sprintf(cs, "%s", "Critical Section Contents\n");
    printf("Wrote in CS: %s\n", cs);
    sem_post(&mutex);
    printf("Exiting CS (write)...\n");
    pthread_exit(0);
}

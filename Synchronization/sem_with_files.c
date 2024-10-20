#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void *readCs(void *arg);
void *writeCs(void *arg);

char cs[40];
sem_t mutex;

const char *filename = "./files/file.txt";

int main() {
    
    sem_init(&mutex, 0, 1);  // Initialize semaphore
    printf("Semaphore initialized.\n");

    pthread_t t1, t2;

    printf("Creating Threads\n");

    int t1_ret = pthread_create(&t1, NULL, writeCs, NULL);
    if (t1_ret != 0) {
        printf("Error creating write thread\n");
        return 1;
    } else {
        printf("Write thread created.\n");
    }

    int t2_ret = pthread_create(&t2, NULL, readCs, NULL);
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
    
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("Error opening file for reading: %s\n", strerror(errno));
        sem_post(&mutex);
        pthread_exit(0);
    }

    char buf[100];
    int bytes_read = read(fd, buf, sizeof(buf) - 1);
    if (bytes_read == -1) {
        printf("Error reading file: %s\n", strerror(errno));
        close(fd);
        sem_post(&mutex);
        pthread_exit(0);
    }
    buf[bytes_read] = '\0';  // Null-terminate the buffer

    printf("Read content: %s\n", buf);

    close(fd);
    sem_post(&mutex);
    printf("Exiting CS (read)...\n");
    pthread_exit(0);
}

void *writeCs(void *arg) {
    printf("Writing to CS...\n");
    printf("Attempting to enter CS...\n");
    sem_wait(&mutex);
    printf("In CS (write)...\n");

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        printf("Error opening file for writing: %s\n", strerror(errno));
        sem_post(&mutex);
        pthread_exit(0);
    }

    const char *data = "Critical Section Contents\n";
    int bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        printf("Error writing to file: %s\n", strerror(errno));
        close(fd);
        sem_post(&mutex);
        pthread_exit(0);
    }

    printf("Wrote in CS: %s\n", data);

    close(fd);
    sem_post(&mutex);
    printf("Exiting CS (write)...\n");
    pthread_exit(0);
}

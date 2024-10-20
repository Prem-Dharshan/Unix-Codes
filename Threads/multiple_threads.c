#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t print_mutex;

void *t_routine(void *arg);

int main() {
    int n;
    printf("Enter the number of threads: ");
    scanf("%d", &n);

    pthread_t threads[n];
    char msgs[n][20];

    pthread_mutex_init(&print_mutex, NULL); // Initialize the mutex

    for (int i = 0; i < n; i++) {
        snprintf(msgs[i], sizeof(msgs[i]), "Thread %d", i);
        
        int t_ret = pthread_create(&threads[i], NULL, t_routine, (void *)msgs[i]);

        if (t_ret != 0) {
            perror("Failed to create thread");
            exit(1);
        }
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&print_mutex); // Destroy the mutex

    return 0;
}

void *t_routine(void *arg) {
    const char *msg = (const char *)arg;

    for (int i = 0; i < 3; i++) {
        pthread_mutex_lock(&print_mutex); // Lock the mutex
        printf("%s ", msg);
        printf("%d\n", i);
        pthread_mutex_unlock(&print_mutex); // Unlock the mutex
        sleep(1);
    }

    pthread_exit(0);
}

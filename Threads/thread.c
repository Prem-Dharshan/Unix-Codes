#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

void *t_routine(void *arg);

int main() {

    pthread_t t1, t2;

    const char *msg1 = "First Thread";
    const char *msg2 = "Second Thread";

    int t1_ret = pthread_create(&t1, NULL, t_routine, (void *) msg1);
    int t2_ret = pthread_create(&t2, NULL, t_routine, (void *) msg2);

    if (t1_ret != 0 || t2_ret != 0) {
        perror("Error creating threads\n");
        exit(1);
    }

    printf("Threads Created\n");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Threads Joined!\n");

    return 0;
}

void *t_routine(void *arg) {

    const char *msg = (const char *)arg;
    int len = strlen(msg);

    for (int i = 0; i < len; i++) {
        printf("%s %d\n", msg, i);
        sleep(1);
    }

    pthread_exit(0);
}

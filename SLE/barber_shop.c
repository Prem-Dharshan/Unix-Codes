#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

void *shop(void *arg);

sem_t waiting_chairs, barber;

typedef struct {
    char name[15];
    int time;
} CustDetail;

int main() {
    pthread_t customers[10];
    CustDetail details[10];
    sem_init(&barber, 0, 1);
    sem_init(&waiting_chairs, 0, 3);

    for (int i = 0; i < 10; i++) {
        sprintf(details[i].name, "Customer %d", i);
        details[i].time = rand() % 10 + 1;
    }

    for (int i = 0; i < 10; i++) {
        pthread_create(&customers[i], NULL, shop, &details[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(customers[i], NULL);
    }

    sem_destroy(&barber);
    sem_destroy(&waiting_chairs);

    return 0;
}

void *shop(void *arg) {
    CustDetail *detail = (CustDetail *)arg;
    int retries = 3;

    while (retries) {
        if (sem_trywait(&waiting_chairs) == 0) {
            sem_wait(&barber);
            printf("Barber cutting hair for %s for %d seconds...\n", detail->name, detail->time);
            sleep(detail->time);
            printf("Barber finished cutting hair for %s.\n", detail->name);
            sem_post(&barber);
            sem_post(&waiting_chairs);
            return NULL;
        } else {
            retries--;
            sleep(10);
        }
    }
    printf("%s found no waiting chairs and is leaving.\n", detail->name);
    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>  // Include time.h for seeding random number generator

void *tunnel(void *arg);

sem_t mutex;
int north_cars = 0, south_cars = 0;

typedef struct {
    char direction[10];
    int time;
    char name[15];
} CarDetail;

int main() {
    pthread_t cars[10];
    CarDetail details[10];
    sem_init(&mutex, 0, 1);
    
    srand(time(NULL));

    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) {
            strcpy(details[i].direction, "North");
            sprintf(details[i].name, "North Car %d", i / 2);
        } else {
            strcpy(details[i].direction, "South");
            sprintf(details[i].name, "South Car %d", i / 2);
        }
        details[i].time = 2;
    }

    for (int i = 0; i < 10; i++) {
        pthread_create(&cars[i], NULL, tunnel, &details[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&mutex);
    return 0;
}

void *tunnel(void *arg) {
    CarDetail *detail = (CarDetail *)arg;

    while (1) {
        if (sem_trywait(&mutex) == 0) {
            if (strcmp(detail->direction, "North") == 0) {
                if (north_cars >= 3) {
                    printf("%s waiting to enter the tunnel...\n", detail->name);
                    sem_post(&mutex);
                    sleep(5);
                    printf("%s %s is retrying...\n", detail->name, detail->direction);
                    continue;   // Retry entering the tunnel
                }
                
                north_cars++;
                printf("%s driving in tunnel for %d seconds...\n", detail->name, detail->time);
                sem_post(&mutex);
                sleep(2);
                sem_wait(&mutex);
                north_cars--;
                printf("%s exiting the tunnel.\n", detail->name);
            } else {
                if (south_cars >= 3) {
                    printf("%s waiting to enter the tunnel...\n", detail->name);
                    sem_post(&mutex);
                    sleep(5);
                    printf("%s %s is retrying...\n", detail->name, detail->direction);
                    continue;   // Retry entering the tunnel
                }
                south_cars++;
                printf("%s driving in tunnel for %d seconds...\n", detail->name, detail->time);
                sem_post(&mutex);
                sleep(2);
                sem_wait(&mutex);
                south_cars--;
                printf("%s exiting the tunnel.\n", detail->name);
            }

            sem_post(&mutex);
            break;  // Exit the loop after handling the car
        } else {
            sleep(5);  // If mutex not acquired, wait before retrying
            printf("%s is retrying...\n", detail->name);
        }
    }

    return NULL;
}

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define NUM_CARS 10
#define MAX_NORTH_CARS 2
#define MAX_SOUTH_CARS 2

pthread_mutex_t mutex;
int north_counter = 0, south_counter = 0;

void* tunnel(void* args) {
    const char* direction = (const char*)args;

    while (1) {
        pthread_mutex_lock(&mutex);

        if (strcmp(direction, "North") == 0) {
            if (south_counter == 0 && north_counter < MAX_NORTH_CARS) {
                north_counter++;
                printf("Car entered in %s direction\n", direction);
                pthread_mutex_unlock(&mutex);
                break;
            }
        } else {  // South direction
            if (north_counter == 0 && south_counter < MAX_SOUTH_CARS) {
                south_counter++;
                printf("Car entered in %s direction\n", direction);
                pthread_mutex_unlock(&mutex);
                break;
            }
        }

        pthread_mutex_unlock(&mutex);
        usleep(100);  // Sleep briefly to avoid busy waiting
    }

    sleep(2);  // Simulate time spent in the tunnel

    pthread_mutex_lock(&mutex);
    if (strcmp(direction, "North") == 0) {
        north_counter--;
        printf("Car exited in %s direction\n", direction);
    } else {
        south_counter--;
        printf("Car exited in %s direction\n", direction);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_CARS];

    // Define car directions as const char* to avoid warnings
    const char* directions[NUM_CARS] = {
        "North", "South", "North", "South", "North",
        "North", "South", "South", "South", "North"
    };

    // Create car threads
    for (int i = 0; i < NUM_CARS; i++) {
        pthread_create(&threads[i], NULL, tunnel, (void*)directions[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_CARS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

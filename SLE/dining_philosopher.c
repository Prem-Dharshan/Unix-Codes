#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *arg);
void eat(int philosopher_number);
void think(int philosopher_number);

int main() {
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);  // Initialize each fork semaphore
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)(intptr_t)i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);  // Clean up semaphores
    }

    return 0;
}

void *philosopher(void *arg) {
    int philosopher_number = (int)(intptr_t)arg;

    // Each philosopher will think and eat once
    think(philosopher_number);
    
    // Pick up forks (left and right)
    int left_fork = philosopher_number;
    int right_fork = (philosopher_number + 1) % NUM_PHILOSOPHERS;

    sem_wait(&forks[left_fork]);  // Pick up left fork
    printf("Philosopher %d picked up left fork %d.\n", philosopher_number, left_fork);
    
    sem_wait(&forks[right_fork]); // Pick up right fork
    printf("Philosopher %d picked up right fork %d.\n", philosopher_number, right_fork);

    eat(philosopher_number);

    // Put down forks
    sem_post(&forks[right_fork]); // Put down right fork
    printf("Philosopher %d put down right fork %d.\n", philosopher_number, right_fork);

    sem_post(&forks[left_fork]);  // Put down left fork
    printf("Philosopher %d put down left fork %d.\n", philosopher_number, left_fork);

    printf("Philosopher %d ate and left the place.\n\n", philosopher_number);
    return NULL;  // Exit the thread after eating
}

void eat(int philosopher_number) {
    printf("Philosopher %d is eating.\n", philosopher_number);
    sleep(1);  // Simulate time taken to eat
}

void think(int philosopher_number) {
    printf("Philosopher %d is thinking.\n", philosopher_number);
    sleep(1);  // Simulate time taken to think
}

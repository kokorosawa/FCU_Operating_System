#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];
pthread_cond_t condition[NUM_PHILOSOPHERS];

void *philosopher(void *arg)
{
    int philosopher_id = *((int *)arg);
    int left_choptstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1)
    {
        // Thinking
        printf("Philosopher %d is thinking\n", philosopher_id);
        usleep(rand() % 1000000);

        // Pick up chopsticks
        pthread_mutex_lock(&chopsticks[left_choptstick]);
        while (pthread_mutex_trylock(&chopsticks[right_chopstick]) != 0)
        {
            // Failed to pick up right chopstick, release left chopstick and retry
            printf("Philosopher %d is waiting for chopstick %d\n", philosopher_id, right_chopstick);
            pthread_cond_wait(&condition[left_choptstick], &chopsticks[left_choptstick]);
            usleep(rand() % 1000000);
            pthread_mutex_unlock(&chopsticks[left_choptstick]);
        }

        // Eating
        printf("Philosopher %d is eating\n", philosopher_id);
        usleep(rand() % 1000000);

        // Put down chopsticks
        pthread_mutex_unlock(&chopsticks[left_choptstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);

        // Notify neighbour that chopsticks are available
        pthread_cond_signal(&condition[left_choptstick]);
        pthread_cond_signal(&condition[right_chopstick]);
    }
}

int main()
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int phil[NUM_PHILOSOPHERS];

    // Initialize mutexes and conditions
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
        pthread_cond_init(&condition[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        phil[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &phil[i]);
    }

    // Wait for philosopher threads to finish (this will never happen in this example)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_join(philosophers[i], NULL);
    }

    // Clean up
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}
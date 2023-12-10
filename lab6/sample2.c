#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5
#define NUM_ROUNDS 5

pthread_mutex_t chopstick[NUM_CHOPSTICKS];
pthread_mutex_t operate;
int failed_attempts[NUM_PHILOSOPHERS] = {0}; // Counter for failed attempts

void *philospher(void *num)
{
    int philosopher_num = *(int *)num;
    int chopstick1 = philosopher_num;
    int chopstick2 = (philosopher_num + 1) % NUM_CHOPSTICKS;

    for (int i = 0; i < NUM_ROUNDS; i++)
    {
        // Wait for chopsticks
        if (pthread_mutex_trylock(&operate) == 0)
        {
            pthread_mutex_lock(&operate);
            pthread_mutex_lock(&chopstick[chopstick1]);
            printf("Philosopher %d has picked up chopstick %d\n", philosopher_num, chopstick1);
            usleep(rand() % 1000000);

            if (pthread_mutex_trylock(&chopstick[chopstick2]) == 0)
            {
                printf("Philosopher %d has picked up chopstick %d\n", philosopher_num, chopstick2);

                // Eating
                printf("Philosopher %d is eating\n", philosopher_num);
                usleep(rand() % 1000000);

                // Releasing chopsticks
                pthread_mutex_unlock(&chopstick[chopstick1]);
                printf("Philosopher %d has released chopstick %d\n", philosopher_num, chopstick1);
                pthread_mutex_unlock(&chopstick[chopstick2]);
                printf("Philosopher %d has released chopstick %d\n", philosopher_num, chopstick2);
            }
            else
            {
                // Failed to acquire second chopstick
                printf("Philosopher %d couldn't pick up chopstick %d. Retrying\n", philosopher_num, chopstick2);

                // Increment failed attempts counter
                failed_attempts[philosopher_num]++;

                // Sleep for a short time before retrying
                usleep(100000);
            }
            pthread_mutex_unlock(&operate);
        }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[NUM_PHILOSOPHERS];
    int phil[NUM_PHILOSOPHERS];

    // Initialize mutexes for chopsticks
    for (int i = 0; i < NUM_CHOPSTICKS; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_CHOPSTICKS; i++)
    {
        phil[i] = i;
        pthread_create(&tid[i], NULL, philospher, &phil[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        printf("Philosopher %d failed to eat %d times\n", i, failed_attempts[i]);
    }

    // Destroy mutexes
    for (int i = 0; i < NUM_CHOPSTICKS; i++)
    {
        pthread_mutex_destroy(&chopstick[i]);
    }

    return 0;
}
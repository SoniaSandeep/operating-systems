#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

pthread_mutex_t chopstick[N];

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        printf("Philosopher %d is THINKING\n", id);
        sleep(1);

        pthread_mutex_lock(&chopstick[id]);
        pthread_mutex_lock(&chopstick[(id + 1) % N]);

        printf("Philosopher %d is EATING\n", id);
        sleep(1);

        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id + 1) % N]);
    }

    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    return 0;
}

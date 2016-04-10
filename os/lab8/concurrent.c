#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

/* global mutex */
pthread_mutex_t mutex;
int global_counter = 0;

void *thread_routine(void *arg) 
{
    /* print and modify global_counter */
    printf("Thread %d says global_counter=%d\n", (int) arg, global_counter);
    global_counter++;

    return NULL;
}

int main(void)
{
    int i;
    pthread_t tids[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_create(&tids[i], NULL, thread_routine, (void *) i);

    for (i = 0; i < NUM_THREADS; i++)
        pthread_join(tids[i], NULL);

    pthread_mutex_destroy(&mutex);
    return 0;
}

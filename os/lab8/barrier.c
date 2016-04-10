#include <string.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

char* str = "ThreadX";
pthread_barrier_t barrier;

void *thread_routine(void *arg)
{
    int rc;
    int thread_idx = (int) arg;

    str[6] = '0' + thread_idx;

    rc = pthread_barrier_wait(&barrier);
    if (rc == PTHREAD_BARRIER_SERIAL_THREAD) {
        printf("Here we go!\n");
    }

    printf("%s\n", str);

    return NULL;
}

int main(void)
{
	int i;
	pthread_t tids[NUM_THREADS];

    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

	for (i = 0; i < NUM_THREADS; i++)
		pthread_create(&tids[i], NULL, thread_routine, (void *) i);

	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(tids[i], NULL);

    pthread_barrier_destroy(&barrier);

	return 0;
}

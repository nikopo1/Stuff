#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS	2
#define MAX_VALUE	128
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
int value = 0;

void* thread_routine1(void *arg)
{
	pthread_mutex_lock(&mutex1);
	pthread_mutex_lock(&mutex2);
	value++;
	pthread_mutex_unlock(&mutex2);
	pthread_mutex_unlock(&mutex1);
	return 0;
}

void* thread_routine2(void *arg)
{
	pthread_mutex_lock(&mutex2);
	pthread_mutex_lock(&mutex1);
	value++;
	pthread_mutex_unlock(&mutex1);
	pthread_mutex_unlock(&mutex2);
	return 0;
}

int main(void)
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, thread_routine1, (void *) NULL);
	pthread_create(&tid2, NULL, thread_routine2, (void *) NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);


	return 0;
}

#include <stdio.h>
#include <pthread.h>

int main(void)
{
	pthread_mutex_t mutex;
	pthread_mutexattr_t attr;

	pthread_mutexattr_init(&attr);
	//pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &attr);

	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);

	pthread_mutex_destroy(&mutex);
	return 0;
}

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *acquire_lock(void *arg)
{
	pthread_mutex_lock(&mutex);
	pthread_exit(NULL);
	return 0;
}

int main(void)
{
	int ret;
	pthread_t tid;

	pthread_create(&tid, NULL, acquire_lock, NULL);
	pthread_join(tid, NULL);

	ret = pthread_mutex_destroy(&mutex);
	if(ret != 0) {
		printf("error destroying mutex (%d)\n", ret);
		return -1;
	}

	return 0;
}

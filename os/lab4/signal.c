#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void my_handle(int signo) { }

int main(void)
{
	//signal(SIGINT, my_handle);
	signal(SIGINT, SIG_IGN);
	sleep(300);
	printf("Hi!\n");
	return 0;
}

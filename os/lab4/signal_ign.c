#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sig_handler(int signum)
{
	printf(" World !");
	signal(SIGINT, SIG_IGN);
}

int main(void)
{
	signal(SIGINT, sig_handler);
	kill(getpid(), SIGINT);
	printf(" Hello ");
	kill(getpid(), SIGINT);
	printf("\n");
	return 0;
}

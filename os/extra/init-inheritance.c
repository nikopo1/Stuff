#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void inline check_return(int assertion, char *err_str)
{
	if(assertion) {
		perror(err_str);
		_exit(-1);
	}
}

int main(void)
{
	int ret;
	pid_t pid;

	pid = fork();
	if(pid < 0) {
		perror("fork failed");
		return -1;
	}

	switch(pid) {
		case 0:
			printf("Child process here, will close fds, sleep for 60s, check ps!\n");
			ret = close(0);
			check_return(ret < 0, "error closing stdin");
			ret = close(1);
			check_return(ret < 0, "error closing stdout");
			ret = close(2);
			check_return(ret < 0, "error closing stderr");
			sleep(60);
			return 0;
		default:
			printf("Parent process here! Exiting ...\n");
			return 0;
	}

	/* never gets here */
	return 0;
}

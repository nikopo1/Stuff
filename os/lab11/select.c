#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE	128

int
main(void)
{
	fd_set rfds;
	struct timeval tv;
	int retval, finished = 0;
	char buffer[BUFFER_SIZE];

	while (!finished) {
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);

		tv.tv_sec = 2;
		tv.tv_usec = 0;

		retval = select(1, &rfds, NULL, NULL, &tv);
		/* Don't rely on the value of tv now! */

		if (retval == -1)
			perror("select()");
		else if (retval)
			printf("Data available.\n");
		else {
			printf("No data within five seconds.\n");
			continue;
		}

		retval = read(0, &buffer, BUFFER_SIZE);
		if (retval == -1)
			perror("read");

		finished = (buffer[x] == 'x');
	}

	printf("Finished.\n");

	exit(EXIT_SUCCESS);
}

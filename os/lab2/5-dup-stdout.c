#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
	close(STDOUT_FILENO);
	dup(fd);
	printf("Hello world!\n");
	return 0;
}

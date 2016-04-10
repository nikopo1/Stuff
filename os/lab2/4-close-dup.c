#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd1, fd2, fd3;
	fd1 = open("in1.txt", O_RDWR);
	fd2 = open("in2.txt", O_RDONLY);
	close(fd1);
	fd3 = dup(fd2);

	printf("fd1=%d fd2=%d fd3=%d\n", fd1, fd2, fd3);

	return 0;
}

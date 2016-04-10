#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd1 = open("myfile", O_RDONLY);
	int pos_fd1 = lseek(fd1, 10, SEEK_SET);
	int fd2 = dup(fd1);
	int pos_fd2 = lseek(fd2, 0, SEEK_CUR);

	printf("fd1=%d, pos_fd1=%d, fd2=%d, pos_fd2=%d\n", fd1, pos_fd1, fd2, pos_fd2);

	return 0;
}

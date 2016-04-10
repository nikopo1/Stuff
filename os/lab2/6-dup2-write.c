#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void)
{
	int error_code;
	int fd1 = open("myfile1", O_CREAT | O_WRONLY | O_TRUNC, 0640);
	int fd2 = open("myfile2", O_CREAT | O_WRONLY | O_TRUNC, 0640);
	fd2 = dup2(fd1, fd2);
	error_code = errno;
	printf("fd2=%d, errno=%d\n", fd2, error_code);
	int written_bytes = write(fd2, "abc", 3);
	error_code = errno;
	printf("written_bytes=%d, errno=%d\n", written_bytes, error_code);
	return 0;
}

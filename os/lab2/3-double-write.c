#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd1 = open("myfile", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	int fd2 = open("myfile", O_WRONLY);

	write(fd1, "abc", 3);
	write(fd2, "xyz", 3);

	close(fd1);
	close(fd2);

	return 0;
}

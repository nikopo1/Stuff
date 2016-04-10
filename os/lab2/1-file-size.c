#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("myfile", O_RDONLY);
	int start_pos = lseek(fd, 0, SEEK_SET);
	int end_pos = lseek(fd, 0, SEEK_END);
	int size = end_pos - start_pos;
	printf("%d\n", size);
	return 0;
}

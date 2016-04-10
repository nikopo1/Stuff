#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>

int main(void)
{
	char *p1, *p2;
	int fd, ret;

	fd = open("myfile", O_CREAT | O_TRUNC | O_RDWR, 0664);
	if(fd < 0)
		return -1;

	ret = ftruncate(fd, 4096);
	if(ret < 0)
		return -1;

	p1 = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, fd, 0);
	if(p1 == NULL)
		return -2;

	p2 = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
	if(p2 == NULL)
		return -3;

	printf("%p, %p\n", p1, p2);

	memcpy(p1, "Hello!\n", 8);

	ret = write(1, p2, 8);
	if(ret < 0)
		return -4;

	ret = close(fd);
	if(ret < 0)
		return -5;

	return 0;
}

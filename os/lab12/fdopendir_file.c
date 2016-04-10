#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <stdio.h>

int main(void)
{
	int fd = open("hello", O_CREAT | O_DIRECTORY, 0755);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	DIR *cdir = fdopendir(fd);
	if (cdir == NULL) {
		perror("fdopendir");
		return -2;
	}

	struct dirent * dirent = readdir(cdir);
	printf("%s\n", dirent->d_name);
	return 0;
}

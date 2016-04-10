#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#define MY_FILE	"myfile.txt"

int main(void)
{
	int fd, backup_fd, ret;

	fd = open(MY_FILE, O_RDWR);
	if (fd < 0) {
		perror("failed open");
		return -1;
	}

	pid_t pid = fork();
	switch (pid) {
	case -1:
		perror("failed fork");
		return -2;
	case 0:
		printf("removing file\n");
		ret = unlink(MY_FILE);
		if (ret < 0) {
			perror("failed unlink");
			return -3;
		}
		return 0;
	default:
		sleep(15);

		printf("recreating file\n");
		backup_fd = open(MY_FILE, O_CREAT | O_WRONLY, 0755);
		if (backup_fd < 0) {
			perror("failed backup create and open");
			return -4;
		}

		ret = sendfile(backup_fd, fd, NULL, 10);
		if (ret < 0) {
			perror("failed sendfile");
			return -5;
		}

		close(fd);
		close(backup_fd);
	}

	wait(NULL);

	return 0;
}

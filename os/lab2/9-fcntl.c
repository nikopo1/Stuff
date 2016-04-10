#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
    int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0600);
    close(STDOUT_FILENO);
    fcntl(fd, F_DUPFD, 0);
    printf("Hello world!\n");
}

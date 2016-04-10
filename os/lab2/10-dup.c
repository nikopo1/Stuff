#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
    creat("output.txt", 0644);
    int fd = open("output.txt", O_RDONLY);
    close(STDOUT_FILENO);
    dup(fd);
    printf("Hello world!\n");
}

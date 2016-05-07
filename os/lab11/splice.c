#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

int main(void)
{
    int ret, fd_src, fd_dst;

    fd_src = open("in.txt", O_RDONLY);
    if (fd_src < 0)
    {
        perror("open failed");
        return -1;
    }

    fd_dst = open("out.txt", O_WRONLY | O_CREAT, 0644);
    if (fd_dst < 0)
    {
        perror("open failed");
        return -1;
    }

    ret = splice(fd_src, NULL, fd_dst, NULL, 16, 0);
    if (ret < 0)
    {
        perror("splice failed");
        return -1;
    }

    close(fd_src);
    close(fd_dst);

    return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
    int x = 0;
    if (fork() || fork())
    {
        x++;
    }

    printf("x=%d, pid=%d\n", x, getpid());

    return 0;
}

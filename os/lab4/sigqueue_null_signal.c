#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
    //int pid = getpid();
    int pid = 0;
    int signo = 0;
    union sigval value;

    int ret = sigqueue(pid, signo, value);
    if (ret < 0)
        printf("%s\n", strerror(errno));
    else
        printf("Exited with %d\n", ret);

    return 0;
}

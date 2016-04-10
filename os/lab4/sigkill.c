#include <signal.h>
#include <stdio.h>

int main(void)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGKILL);
    sigprocmask(SIG_BLOCK, &set, NULL);
    while (1) {
        printf ("Running!");
    }

    return 0;
}

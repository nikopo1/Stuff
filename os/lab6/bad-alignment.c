#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define DIE(assertion, call_description)                                \
        do {                                                            \
                if (assertion) {                                        \
                        fprintf(stderr, "(%s, %d): ",                   \
                                        __FILE__, __LINE__);            \
                        perror(call_description);                       \
                        exit(EXIT_FAILURE);                             \
                }                                                       \
        } while(0)

int main(void)
{
        int ret;
        char *addr;

        addr = mmap(NULL, 4096, PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
        DIE(addr == NULL, "mmap");

        ret = mprotect(&addr[1024], 24, PROT_WRITE);
        DIE(ret < 0, "mprotect");

        memcpy(&addr[1024], "Hope clouds observation.", 24);
        printf("%s\n", &addr[1024]);

        ret = munmap(addr, 4096);
        DIE(ret < 0, "munmap");

        return 0;
}

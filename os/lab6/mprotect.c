#define DIE(assertion, call_description)                                \
        do {                                                            \
                if (assertion) {                                        \
                        fprintf(stderr, "(%s, %d): ",                   \
                                        __FILE__, __LINE__);            \
                        perror(call_description);                       \
                        exit(EXIT_FAILURE);                             \
                }                                                       \
        } while(0)

#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void){
        int ret;
        char *addr;

        addr = mmap(NULL, 2 * 4096, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
        DIE (addr == MAP_FAILED, "Eroare mmap");

        ret = mprotect(addr, 4097, PROT_READ);
        DIE (ret < 0, "Eroare mprotect");

        memcpy(&addr[6144], "Hope clouds observation.", 24);
        printf("%s\n", &addr[6144]);

        ret = munmap(addr, 2*4096);
        DIE( ret < 0, "Eroare munmap");

        return 0;
}

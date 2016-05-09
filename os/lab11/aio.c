#include <libaio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

#define NUM_AIO_OPS 4

/* file names */
static char *files[] = {
    "./slo.txt",
    "./oer.txt",
    "./rse.txt",
    "./ufver.txt"
};

int main(void)
{
    int i, rc;
    int fds[NUM_AIO_OPS];
    struct iocb iocb[NUM_AIO_OPS];
    struct iocb *piocb[NUM_AIO_OPS];
    struct io_event events[NUM_AIO_OPS];
    char buffer[] = "Fear is the mind-killer.";
    io_context_t ctx = 0;

    for (i = 0; i < NUM_AIO_OPS; i++) {
        fds[i] = open(files[i], O_RDONLY | O_CREAT | O_TRUNC, 0644);
        if (fds[i] < 0) {
            perror("open failed");
            return -1;
        }
    }

    fds[3] = fds[1];

    for (i = 0; i < NUM_AIO_OPS; i++) {
        piocb[i] = &iocb[i];
        io_prep_pwrite(&iocb[i], fds[i], buffer, sizeof(buffer) - 1, 0);
    }

    if (io_setup(NUM_AIO_OPS, &ctx) < 0) {
        perror("io_setup failed");
        return -1;
    }

    rc = io_submit(ctx, NUM_AIO_OPS, piocb);
//    if (rc < 0) {
//        printf("%d\n", rc);
//        perror("io_submit failed");
//        return -1;
//    }

    rc = io_getevents(ctx, NUM_AIO_OPS, NUM_AIO_OPS, events, NULL);
    if (rc < 0) {
        perror("io_getevents failed");
        return -1;
    }

    if (io_destroy(ctx) < 0) {
        perror("io_destroy failed");
        return -1;
    }

    return 0;
}

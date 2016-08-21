#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

#define FILE_NAME_1 "../ceva"
#define FILE_NAME_2 "atreides"

int main(int argc, char* argv[])
{
    int ret;
    struct stat file_stat;

    ret = symlink(FILE_NAME_1, FILE_NAME_2);
    if (ret < 0) {
        perror("symlink");
        return -1;
    }

    ret = lstat(FILE_NAME_2, &file_stat);
    if (ret < 0) {
        perror("lstat");
        return -1;
    }

    printf("file size = %d\n", file_stat.st_size);

    return 0;
}

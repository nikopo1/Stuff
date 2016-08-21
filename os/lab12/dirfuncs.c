#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <libgen.h>

#include <stdio.h>

int main(void)
{
    char *path = "/bin/ls";
    char *dname = dirname(path);
    char *bname = basename(path);

    printf("dirname = %s, basename = %s\n", dname, bname);
	return 0;
}

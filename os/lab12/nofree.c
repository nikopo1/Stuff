#define _GNU_SOURCE
#include <unistd.h>

#include <stdio.h>

void print_current_dir(void) {
    char *cwd = get_current_dir_name();
    printf("%s\n", cwd);
}

int main(void)
{
    print_current_dir();
    return 0;
}

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *const argv[] = { "ls", "-la", NULL};
	char *const envp[] = {};

	execve("/bin/ls", argv, envp);
	printf("Hello!\n");

	return 0;
}

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *path = malloc(100 * sizeof(char));
	char *result = getcwd(path, 10 * sizeof(char));
	if(result == NULL) {
		perror("null result");
		return -1;
	}
	printf("%s\n", path);
	return 0;
}

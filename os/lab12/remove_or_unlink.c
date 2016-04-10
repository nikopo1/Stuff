#include <unistd.h>
#include <stdio.h>

#define SYMLINK_NAME	"arrakis"

int main(int argc, char* argv[])
{
	int ret = symlink(argv[0], SYMLINK_NAME);
	if (ret < 0) {
		perror("symlink");
		return -1;
	}

	ret = remove(SYMLINK_NAME);
	if (ret < 0) {
		perror("remove");
		return -2;
	}
	return 0;
}

#include <unistd.h>

int main(void)
{
	int ret = mount("/dev/sdb1", "/media/cristian", "vfat", 0, NULL);
	if (ret < 0) {
		perror("mount");
		return -1;
	}

	ret = umount("/dev/sdb1");
	if (ret < 0) {
		perror("umount");
		return -2;
	}

	return 0;
}

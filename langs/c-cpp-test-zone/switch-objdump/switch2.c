#include <stdio.h>

void print(int msg_no)
{
	switch(msg_no) {
	case 1:
		printf("something\n");
		break;
	case 2 ... 4:
		printf("interesting\n");
		break;
	default:
		printf("error\n");
		break;
	}
}

int main(void)
{
	print(1);
	print(2);
	print(6);
	return 0;
}

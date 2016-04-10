#include <stdio.h>

int idx = 5;

int main(void)
{
	if(idx > 0) {
		printf("%d\n", idx);
		idx--;
		return main();
	}
	return 0;
}

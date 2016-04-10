#include <stdio.h>

int main(void) {
	char *str = "... fear is the mind-killer.";
	str[4] = 'F';
	printf("%s\n", str);
	return 0;
}

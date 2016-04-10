#include <stdio.h>

int main(void)
{
	int number = 1;
	char x = '%';
	switch(x) {
	default:
	case '+': number += 1;
	case '-': number -= 1;
	case '*': number *= 10;
	}
	printf("%d\n", number);
	return 0;
}

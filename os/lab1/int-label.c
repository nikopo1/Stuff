#include <stdio.h>

int main(void) {
	{int i=10; goto lbl;}

	{int i=20;
		{int i=30; lbl:;}
		printf("%i", ++i);
	}
	return 0;
}

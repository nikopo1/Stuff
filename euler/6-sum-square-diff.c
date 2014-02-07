#include <stdio.h>

#define SUM_SQ_CONS(n) ((2*(n)*(n)*(n) + 3*(n)*(n) + n)/6)
#define SUM_CONS(n) (((n)*((n) + 1))/2)

int main(void)
{
	printf("%d\n", SUM_CONS(100)*SUM_CONS(100) - SUM_SQ_CONS(100));
	return 0;
}

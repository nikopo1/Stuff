#include <stdio.h>

#define MY_AVG(a, b, c)	(a + b) / c


int main(void)
{
    int a = 13;
    int b = 17;
    int c = 4;

    /*
     * The macro translates to (a + b) / c + 1. So, 30 / 4 + 1 = 8.
     */
    printf("%d\n", MY_AVG(a, b, c + 1));
    return 0;
}

#include <stdio.h>

int main(void)
{
int z;
int x = 5;
int y = -10;
int a = 4;int b = 2;

printf("x=%d, y=%d, z=%d, a=%d, b=%d\n", x, y, z, a, b);

z = x++ + ++y * b / a;

// 5 + -10 * 2 / 4
// 5 + 5 = 0

printf("x=%d, y=%d, z=%d, a=%d, b=%d\n", x, y, z, a, b);

return 0;
}

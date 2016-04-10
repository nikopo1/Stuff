#include <stdio.h>

int main(void)
{
    int i;
    int buffer[10];
    int my_variable = 0xdeadf00d;

    for (i = 0; i <= 10; i++)
    {
        buffer[i] = i * 10;
    }

    printf("%d\n", my_variable);

    return 0;
}

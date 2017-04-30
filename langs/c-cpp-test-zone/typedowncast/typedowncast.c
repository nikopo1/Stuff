#include <stdio.h>

#define DEMOTE1_EQ(var1, var2)    \
    (((typeof(var2))(var1)) == (var2))

#define DEMOTE2_EQ(var1, var2)    \
    ((var1) == ((typeof(var1))(var2)))

int main(void)
{
    int a = 0xFFFF0001;
    char b = 0x01;

    if (DEMOTE1_EQ(a, b))
    {
        printf("Equal!\n");
    }
    else
    {
        printf("Not equal!\n");
    }

    if (DEMOTE2_EQ(a, b))
    {
        printf("Equal!\n");
    }
    else
    {
        printf("Not equal!\n");
    }

    return 0;
}

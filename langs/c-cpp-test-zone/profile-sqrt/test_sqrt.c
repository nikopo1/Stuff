#include <stdio.h>
#include <stdint.h>

unsigned int isqrt32(unsigned int n)
{
    register unsigned int root, remainder, place;

    root = 0;
    remainder = n;
    place = 0x40000000;

    while (place > remainder)
        place = place >> 2;

    while (place)
    {
        if (remainder >= root + place)
        {
            remainder = remainder - root - place;
            root = root + (place << 1);
        }
        root = root >> 1;
        place = place >> 2;
    }

    return root;
}

unsigned short isqrt(unsigned int a) {
    register unsigned int rem = 0;
    register unsigned int root = 0;
    int i;

    for (i = 0; i < 16; i++) {
        root <<= 1;
        rem <<= 2;
        rem += a >> 30;
        a <<= 2;

        if (root < rem) {
            root++;
            rem -= root;
            root++;
        }
    }

    return (unsigned short) (root >> 1);
}

int main(void)
{
    unsigned int sum = 0;
    for (unsigned int i = 0; i < 100000000; i++)
    {
        //printf("%d: %d, %d\n", i, isqrt32(i), isqrt(i));
        sum += isqrt32(i);
        //sum += isqrt(i);
    }

    printf("%u\n", sum);

    return 0;
}

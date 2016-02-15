#include <stdint.h>
#include <stdio.h>
#include <string.h>


static const uint8_t s[] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static const uint32_t k[] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};


static inline uint32_t leftrotate(uint32_t val, uint8_t count)
{
    return (val << count) | (val >> (32 - count));
}


void print_hex(const unsigned char* addr, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++)
    {
        if (i > 0 && i % 4 == 0)
        {
            printf(" ");
        }

        if (i > 0 && i % 16 == 0)
        {
            printf("\n");
        }

        printf("%02x", addr[i]);
    }

    printf("\n");
}


void encode(uint32_t* input, unsigned char* output, unsigned int size)
{
    unsigned int i, j;

    for (i = 0, j = 0; j < size; i++, j += 4)
    {
        output[j]   = (unsigned char)(input[i] & 0xff);
        output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
        output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
        output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
    }
}


void md5(const void* addr, unsigned int size, uint32_t* hash)
{
    uint32_t msg[16] = {0};

    memset(msg, 0, sizeof(msg));
    memcpy(msg, "The quick brown fox jumps over the lazy dog.", 44);

    msg[11] = 0x00000080;

    uint64_t value = 44 * 8;

    encode((uint32_t*)&value, (unsigned char*)&msg[14], 8);

    uint32_t a0 = 0x67452301;
    uint32_t b0 = 0xefcdab89;
    uint32_t c0 = 0x98badcfe;
    uint32_t d0 = 0x10325476;

    uint32_t a = a0;
    uint32_t b = b0;
    uint32_t c = c0;
    uint32_t d = d0;
    uint32_t f;
    uint32_t g;
    uint32_t dtemp;

    for (int i = 0; i < 64; i++)
    {
        if (0 <= i && i <= 15)
        {
            f = (b & c) | (~b & d);
            g = i;
        }
        else if (16 <= i && i <= 31)
        {
            f = (d & b) | (~d & c);
            g = (5 * i + 1) % 16;
        }
        else if (32 <= i && i <= 47)
        {
            f = b ^ c ^ d;
            g = (3 * i + 5) % 16;
        }
        else if (48 <= i && i <= 63)
        {
            f = c ^ (b | ~d);
            g = (7 * i) % 16;
        }

        dtemp = d;
        d = c;
        c = b;
        b = b + leftrotate(a + f + k[i] + msg[g], s[i]);
        a = dtemp;
    }

    a0 += a;
    b0 += b;
    c0 += c;
    d0 += d;

    print_hex((const char*)msg, sizeof(msg));

    hash[0] = a0;
    hash[1] = b0;
    hash[2] = c0;
    hash[3] = d0;
}


int main(void)
{
    uint8_t hash[16];

    md5(NULL, 10, hash);

    for (int i = 0; i < 16; i++)
    {
        printf("%02x", hash[i]);
    }

    printf("\n");

    return 0;
}

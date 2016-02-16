#include <stdint.h>
#include <stdio.h>
#include <string.h>


#define MD5_CHUNK_SIZE      64


static void print_hex(const unsigned char* addr, unsigned int size)
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


static void md5_encode(const uint32_t* msg, uint32_t* hash)
{
    uint32_t a = hash[0];
    uint32_t b = hash[1];
    uint32_t c = hash[2];
    uint32_t d = hash[3];
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

    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
}


void md5(const char* msg, unsigned int size, uint32_t* hash)
{
    char chunk[MD5_CHUNK_SIZE];

    hash[0] = 0x67452301;
    hash[1] = 0xefcdab89;
    hash[2] = 0x98badcfe;
    hash[3] = 0x10325476;

    unsigned int num_chunks = (size / MD5_CHUNK_SIZE) + (size % MD5_CHUNK_SIZE != 0);

    if ((size + 1) % MD5_CHUNK_SIZE > MD5_CHUNK_SIZE - sizeof(uint64_t))
    {
        num_chunks++;
    }

    unsigned int hashed_size = 0;

    while (size - hashed_size >= MD5_CHUNK_SIZE)
    {
        memcpy(chunk, &msg[hashed_size], MD5_CHUNK_SIZE);
        md5_encode((uint32_t*)chunk, hash);
        hashed_size += MD5_CHUNK_SIZE;
    }

    /* Set the first bit after the data being hashed. */
    memcpy(chunk, &msg[hashed_size], size - hashed_size);
    chunk[size - hashed_size] = 0x80;
    memset(&chunk[size - hashed_size + 1], 0, MD5_CHUNK_SIZE - (size - hashed_size + 1));

    if ((size + 1) % MD5_CHUNK_SIZE > 56)
    {
        /* Hash an extra block, hashed data length doesn't fit in this block. */
        md5_encode((uint32_t*)chunk, hash);

        memset(chunk, 0, MD5_CHUNK_SIZE);
        uint64_t length = size * 8;
        memcpy(&chunk[MD5_CHUNK_SIZE - 8], &length, 8);
        md5_encode((uint32_t*)chunk, hash);
    }
    else
    {
        /* Write hashed data length in the current block, it fits. */
        uint64_t length = size * 8;
        memcpy(&chunk[MD5_CHUNK_SIZE - 8], &length, 8);
        md5_encode((uint32_t*)chunk, hash);
    }

    print_hex(chunk, MD5_CHUNK_SIZE);
}


int main(int argc, char* argv[])
{
    uint8_t hash[16];
    FILE* f = NULL;

    //char* text = "The quick brown fox jumps over the lazy dog.";
    //md5(text, 44, (uint32_t*)hash);

    if (argc != 2)
    {
        printf("Usage: %s file\n\n", argv[0]);
        return -1;
    }

    f = fopen(argv[1], "r");
    if (!f)
    {
        printf("File %s could not be opened\n", argv[1]);
        return -2;
    }

    char buffer[4096];
    int size;
    size = fread(buffer, 1, 4096, f);
    if (size < 0)
    {
        printf("Couldn't read data\n");
        return -3;
    }

    md5(buffer, size, (uint32_t*)hash);

    for (int i = 0; i < 16; i++)
    {
        printf("%02x", hash[i]);
    }

    printf("\n");

    return 0;
}

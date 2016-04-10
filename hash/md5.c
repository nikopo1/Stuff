#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "md5.h"
#include "resource_manager_fake_resources.h"


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

/**
 * \brief Left-rotates the bits of the given value with the specified amount of positions.
 *
 * \param val   The value to left-rotate.
 * \param count Number of bit positions to rotate.
 *
 * \return The rotated value.
 */
static inline uint32_t _leftrotate(uint32_t val, uint8_t count);

/**
 * \brief Runs the hashing rounds specified in MD5 RFC 1321 on a 512-bit block.
 *
 * \param address   Pointer to the start of the 512-bit block.
 * \param hash      Pointer to a 128-bit array containing the hash computed so far.
 *
 * \note For the first block, the hash must be contain the values specified in RFC 1321.
 */
static void _hash_block(const void* msg, uint32_t* hash);


/**
 * \brief Number of bits to shift per round.
 */
static const uint8_t g_round_shift[] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

/**
 * \brief Sines of angles expressed in radians. See the following function.
 *
 * sine_rad[angle] = (2^32 * abs(sin(angle + 1))) mod 2^32, where angle is expressed in radians.
 */
static const uint32_t g_sine_radians[] = {
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


void md5_init(struct md5_context* context)
{
    context->hash[0] = 0x67452301;
    context->hash[1] = 0xefcdab89;
    context->hash[2] = 0x98badcfe;
    context->hash[3] = 0x10325476;
    context->length = 0;
}


void md5_update(struct md5_context* context, const uint8_t* msg, uint64_t size)
{
    uint32_t offset = 0;

    while (size > 0)
    {
        uint16_t chunk_offset = context->length % MD5_CHUNK_SIZE;
        uint16_t chunk_left = MD5_CHUNK_SIZE - chunk_offset;

        if (chunk_left <= size)
        {
            memcpy(&context->chunk[chunk_offset], &msg[offset], chunk_left);
            _hash_block(context->chunk, context->hash);
            context->length += chunk_left;
            offset += chunk_left;
            size -= chunk_left;
        }
        else
        {
            memcpy(&context->chunk[chunk_offset], &msg[offset], size);
            context->length += size;
            return;
        }
    }
}


void md5_final(struct md5_context* context)
{
    uint16_t chunk_offset = context->length % MD5_CHUNK_SIZE;
    uint16_t chunk_left = MD5_CHUNK_SIZE - chunk_offset;
    uint64_t bit_length = context->length * 8;

    context->chunk[chunk_offset] = 0x80;
    memset(&context->chunk[chunk_offset + 1], 0, chunk_left - 1);

    printf("context->length = %u, chunk_left = %u, chunk_offset = %u\n", context->length, chunk_left, chunk_offset);

    if (chunk_left - 1 < sizeof(uint64_t))
    {
        printf("Passes through here\n");
        _hash_block(context->chunk, context->hash);
        memset(context->chunk, 0, MD5_CHUNK_SIZE);
    }

    memcpy(&context->chunk[MD5_CHUNK_SIZE - sizeof(uint64_t)], &bit_length, sizeof(uint64_t));
    _hash_block(context->chunk, context->hash);
}


static inline uint32_t _leftrotate(uint32_t val, uint8_t count)
{
    return (val << count) | (val >> (32 - count));
}


static void _hash_block(const void* address, uint32_t* hash)
{
    const uint32_t* msg = address;
    uint32_t a = hash[0];
    uint32_t b = hash[1];
    uint32_t c = hash[2];
    uint32_t d = hash[3];
    uint32_t f = 0;
    uint32_t g = 0;
    uint32_t dtemp;

    //print_hex(address, MD5_CHUNK_SIZE);

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
        b = b + _leftrotate(a + f + g_sine_radians[i] + msg[g], g_round_shift[i]);
        a = dtemp;
    }

    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
}


void compute_hash(const uint8_t* address, unsigned int size)
{
    unsigned int i;
    struct md5_context context;

    md5_init(&context);

    for (i = 0; i < size; i++)
    {
        md5_update(&context, &address[i], 1);
    }

    md5_final(&context);

    for (i = 0; i < 4; i++)
    {
        printf("%x ", context.hash[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[])
{
    FILE* f = NULL;

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

    compute_hash(large_resource_1_data, sizeof(large_resource_1_data));
    compute_hash(small_resource_1_data, sizeof(small_resource_1_data));

    struct md5_context context;

    char buffer[21];
    int size;

    md5_init(&context);

    while (size = fread(buffer, 1, sizeof(buffer), f))
    {
        md5_update(&context, buffer, size);
    }

    md5_final(&context);

    uint8_t* hash = (uint8_t*)&context.hash;

    for (int i = 0; i < 16; i++)
    {
        printf("%02x", hash[i]);
    }

    printf("\n");

    return 0;
}

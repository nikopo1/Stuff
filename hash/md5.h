/**
 /**
 * \file
 *
 * \brief MD5 hash function declarations.
 *
 * Copyright (c) 2016 VectorWatch. All rights reserved.
 */

#ifndef _MD5_H
#define _MD5_H

#include <stdint.h>


/**
 * \brief The chunk size used when computing the MD5 hash, always 64 bytes.
 */
#define MD5_CHUNK_SIZE      64

/**
 * \brief Structure which holds the current context of an MD5 hash computation.
 */
struct __attribute__((packed)) md5_context {
    uint8_t chunk[MD5_CHUNK_SIZE];  /**< Buffer used to hold data for the current block. */
    uint16_t length;                /**< Bytes written in this hash computation so far. */
    uint32_t hash[4];               /**< Current hash, holds the final sum after md5_final(). */
};


/**
 * \brief Initializes the MD5 context structure.
 *
 * \param context   Pointer to the MD5 context structure which will be initialized.
 */
void md5_init(struct md5_context* context);

/**
 * \brief Add size number of bytes, held in the msg buffer, to the currently computed MD5.
 *
 * \param context   Pointer to the MD5 context structure used to compute the hash.
 * \param msg       Buffer which holds additional bytes.
 * \param size      The number of bytes to add, which are held in the buffer.
 */
void md5_update(struct md5_context* context, const uint8_t* msg, uint64_t size);

/**
 * \brief Finalizes the MD5 hash computation. The context->hash field holds the final MD5 hash.
 *
 * \param context   Pointer to the MD5 context structure used to compute the hash.
 */
void md5_final(struct md5_context* context);

#endif /* _MD5_H */

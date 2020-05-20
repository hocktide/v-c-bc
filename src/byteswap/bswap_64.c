/**
 * \file byteswap/bswap_64.c
 *
 * \brief Byte swap a 64-bit integer.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <vcblockchain/byteswap.h>

/**
 * \brief Swap the endian representation of a given 64-bit value.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
int64_t bswap_64(int64_t val)
{
    uint64_t v = (uint64_t)val;

    /* swap dword high / low. */
    v = ((v & 0xFFFFFFFF00000000UL) >> 32) | ((v & 0x00000000FFFFFFFFUL) << 32);
    /* swap word high / low. */
    v = ((v & 0xFFFF0000FFFF0000UL) >> 16) | ((v & 0x0000FFFF0000FFFFUL) << 16);
    /* swap byte high / low. */
    v = ((v & 0xFF00FF00FF00FF00UL) >> 8) | ((v & 0x00FF00FF00FF00FFUL) << 8);

    return v;
}

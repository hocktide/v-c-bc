/**
 * \file byteswap/htonll.c
 *
 * \brief Perform a host to network order conversion on a 64-bit value.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <vcblockchain/byteswap.h>

/**
 * \brief Perform a host to network byte order swap operation.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
int64_t htonll(int64_t val)
{
#ifdef VCBLOCKCHAIN_LITTLE_ENDIAN
    return bswap_64(val);
#else
    return val;
#endif
}

/**
 * \file vcblockchain/byteswap.h
 *
 * \brief Byteswap routines.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#ifndef VCBLOCKCHAIN_BYTESWAP_HEADER_GUARD
#define VCBLOCKCHAIN_BYTESWAP_HEADER_GUARD

#include <stdint.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/**
 * \brief Swap the endian representation of a given 32-bit value.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
inline int32_t bswap_32(int32_t val)
{
    uint32_t v = (uint32_t)val;

    return ((v & 0xFF000000) >> 24) | ((v & 0x00FF0000) >> 8) | ((v & 0x0000FF00) << 8) | ((v & 0x000000FF) << 24);
}

/**
 * \brief Swap the endian representation of a given 64-bit value.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
inline int64_t bswap_64(int64_t val)
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

/**
 * \brief Perform a host to network byte order swap operation.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
inline int32_t htonl(int32_t val)
{
#ifdef LITTLE_ENDIAN
    return bswap_32(val);
#else
    return val;
#endif
}

/**
 * \brief Perform a network to host byte order swap operation.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
inline int32_t ntohl(int32_t val)
{
#ifdef LITTLE_ENDIAN
    return bswap_32(val);
#else
    return val;
#endif
}

/**
 * \brief Perform a host to network byte order swap operation.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
inline int64_t htonll(int64_t val)
{
#ifdef LITTLE_ENDIAN
    return bswap_64(val);
#else
    return val;
#endif
}

/**
 * \brief Perform a network to host byte order swap operation.
 *
 * \param val       The value to swap.
 *
 * \returns the swapped value.
 */
inline int64_t ntohll(int64_t val)
{
#ifdef LITTLE_ENDIAN
    return bswap_64(val);
#else
    return val;
#endif
}

/* make this header C++ friendly. */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*VCBLOCKCHAIN_BYTESWAP_HEADER_GUARD*/

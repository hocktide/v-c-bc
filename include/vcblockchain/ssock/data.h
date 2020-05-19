/**
 * \file vcblockchain/ssock/data.h
 *
 * \brief Data structure definitions for ssock.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#ifndef VCBLOCKCHAIN_SSOCK_DATA_HEADER_GUARD
#define VCBLOCKCHAIN_SSOCK_DATA_HEADER_GUARD

#include <stddef.h>
#include <vpr/disposable.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/* forward decl for ssock. */
typedef struct ssock ssock;

/* packet types. */
#define SSOCK_DATA_TYPE_BOM 0x00
#define SSOCK_DATA_TYPE_UINT8 0x01
#define SSOCK_DATA_TYPE_UINT32 0x03
#define SSOCK_DATA_TYPE_UINT64 0x04
#define SSOCK_DATA_TYPE_INT8 0x09
#define SSOCK_DATA_TYPE_INT32 0x0A
#define SSOCK_DATA_TYPE_INT64 0x0B
#define SSOCK_DATA_TYPE_STRING 0x10
#define SSOCK_DATA_TYPE_DATA_PACKET 0x20
#define SSOCK_DATA_TYPE_AUTHED_PACKET 0x30
#define SSOCK_DATA_TYPE_EOM 0xFF

/**
 * \brief Read method for ssock.
 *
 * \param sock      The ssock instance to read from.
 * \param buf       The buffer to read bytes into.
 * \param size      Pointer to the size value. As input, it is the number of
 *                  bytes to read from this ssock.  On success, the number of
 *                  bytes read will be saved to this variable.
 *
 * \returns a status code indicating success or failure.
 *      - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*ssock_read_fn)(ssock* sock, void* buf, size_t* size);

/**
 * \brief Write method for ssock.
 *
 * \param sock      The ssock instance to write to.
 * \param buf       The buffer to write bytes into the socket from.
 * \param size      Pointer to the size value. As input, it is the number of
 *                  bytes to write to this ssock.  On success, the number of
 *                  bytes written will be saved to this variable.
 *
 * \returns a status code indicating success or failure.
 *      - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
typedef int (*ssock_write_fn)(ssock* sock, const void* buf, size_t* size);

/**
 * \brief The ssock abstraction provides a read and write method for reading
 * from or writing to a socket.
 */
struct ssock
{
    /** \brief ssock is disposable. */
    disposable_t hdr;

    /** \brief read method for ssock. */
    ssock_read_fn read;

    /** \brief read method for ssock. */
    ssock_write_fn write;

    /** \brief context for ssock. */
    void* context;
};

/* make this header C++ friendly. */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*VCBLOCKCHAIN_SSOCK_DATA_HEADER_GUARD*/

/**
 * \file vcblockchain/ssock.h
 *
 * \brief Simple socket abstraction for vcblockchain.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#ifndef VCBLOCKCHAIN_SSOCK_HEADER_GUARD
#define VCBLOCKCHAIN_SSOCK_HEADER_GUARD

#include <stddef.h>
#include <vcblockchain/error_codes.h>
#include <vcblockchain/ssock/data.h>

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/**
 * \brief Initialize a ssock instance from a POSIX socket descriptor.
 *
 * This instance takes over ownership of the socxet descriptor. This instance is
 * disposable and must be disposed by calling \ref dispose() when no longer
 * needed.  Note that \ref dispose() will close the underlying socket
 * descriptor.
 *
 * \param sock              The ssock instance to initialize.
 * \param sd                The socket descriptor to use for this instance.
 *
 * \returns a status code indicating success or failure.
 *      - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int ssock_init_from_posix(ssock* sock, int sd);

/**
 * \brief Read data from a ssock instance.
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
int ssock_read(ssock* sock, void* buf, size_t* size);

/**
 * \brief Write data to a ssock instance.
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
int ssock_write(ssock* sock, const void* buf, size_t* size);

/* make this header C++ friendly. */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*VCBLOCKCHAIN_SSOCK_HEADER_GUARD*/

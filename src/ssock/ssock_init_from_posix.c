/**
 * \file src/ssock/ssock_init_from_posix.c
 *
 * \brief Initialize a ssock instance from a POSIX socket descriptor.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <string.h>
#include <unistd.h>
#include <vcblockchain/ssock.h>

/* forward decls. */
static int ssock_posix_read(ssock*, void*, size_t*);
static int ssock_posix_write(ssock*, const void*, size_t*);
static void ssock_posix_dispose(void*);

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
int ssock_init_from_posix(ssock* sock, int sd)
{
    /* parameter sanity checks. */
    MODEL_ASSERT(NULL != sock);
    MODEL_ASSERT(sd >= 0);

    /* runtime parameter checks. */
    if (NULL == sock || sd < 0)
    {
        return VCBLOCKCHAIN_ERROR_INVALID_ARG;
    }

    /* configure ssock instance. */
    memset(sock, 0, sizeof(ssock));
    sock->hdr.dispose = &ssock_posix_dispose;
    sock->read = &ssock_posix_read;
    sock->write = &ssock_posix_write;
    sock->context = (void*)((long)sd);

    /* success. */
    return VCBLOCKCHAIN_STATUS_SUCCESS;
}

/**
 * \brief Read from a POSIX socket.
 *
 * \param sock      The socket to read from.
 * \param buf       The buffer to read into.
 * \param size      On input, the number of bytes to read; on output, the number
 *                  of bytes read.
 *
 * \returns a status code indicating success or failure.
 *          - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *          - a non-zero error code on failure.
 */
static int ssock_posix_read(ssock* sock, void* buf, size_t* size)
{
    int sd = -1;

    /* parameter sanity checks. */
    MODEL_ASSERT(NULL != sock);
    MODEL_ASSERT(NULL != buf);
    MODEL_ASSERT(NULL != size);

    /* get the socket descriptor from the context pointer. */
    sd = (int)((long)sock->context);

    /* attempt to read bytes from the socket. */
    ssize_t bytes_read = read(sd, buf, *size);
    if (bytes_read < 0)
    {
        return VCBLOCKCHAIN_ERROR_SSOCK_READ;
    }

    /* save the number of bytes read to size. */
    *size = bytes_read;

    /* success. */
    return VCBLOCKCHAIN_STATUS_SUCCESS;
}

/**
 * \brief Write to a POSIX socket.
 *
 * \param sock      The socket to write to.
 * \param buf       The buffer to write from.
 * \param size      On input, the number of bytes to write; on output, the
 *                  number of bytes written.
 *
 * \returns a status code indicating success or failure.
 *          - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *          - a non-zero error code on failure.
 */
static int ssock_posix_write(ssock* sock, const void* buf, size_t* size)
{
    int sd = -1;

    /* parameter sanity checks. */
    MODEL_ASSERT(NULL != sock);
    MODEL_ASSERT(NULL != buf);
    MODEL_ASSERT(NULL != size);

    /* get the socket descriptor from the context pointer. */
    sd = (int)((long)sock->context);

    /* attempt to write bytes to the socket. */
    ssize_t bytes_written = write(sd, buf, *size);
    if (bytes_written < 0)
    {
        return VCBLOCKCHAIN_ERROR_SSOCK_WRITE;
    }

    /* save the number of bytes written to size. */
    *size = bytes_written;

    /* success. */
    return VCBLOCKCHAIN_STATUS_SUCCESS;
}

/**
 * \brief Dispose of a ssock instance.
 *
 * \param sock      The socket to write to.
 * \param buf       The buffer to write from.
 * \param size      On input, the number of bytes to write; on output, the
 *                  number of bytes written.
 *
 * \returns a status code indicating success or failure.
 *          - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *          - a non-zero error code on failure.
 */
static void ssock_posix_dispose(void* disposable)
{
    ssock* sock = (ssock*)disposable;

    /* parameter sanity check. */
    MODEL_ASSERT(NULL != sock);

    /* get the socket descriptor. */
    int sd = (int)((long)sock->context);

    /* close this descriptor. */
    close(sd);
}

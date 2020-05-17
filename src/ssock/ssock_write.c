/**
 * \file src/ssock/ssock_write.c
 *
 * \brief Write data to a ssock instance.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <cbmc/model_assert.h>
#include <vcblockchain/ssock.h>

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
int ssock_write(ssock* sock, const void* buf, size_t* size)
{
    MODEL_ASSERT(NULL != sock);
    MODEL_ASSERT(NULL != buf);
    MODEL_ASSERT(NULL != size);

    /* runtime sanity check on parameters. */
    if (NULL == sock || NULL == buf || NULL == size)
        return VCBLOCKCHAIN_ERROR_INVALID_ARG;

    return sock->write(sock, buf, size);
}

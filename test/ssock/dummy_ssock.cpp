/**
 * \file test/ssock/dummy_ssock.cpp
 *
 * Dummy ssock implementation, used for testing.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <algorithm>

#include "dummy_ssock.h"

using namespace std;

/* forward decls. */
static int dummy_ssock_read(ssock* sock, void* buf, size_t* size);
static int dummy_ssock_write(ssock* sock, const void* buf, size_t* size);
static void dummy_ssock_dispose(void* sock);

/**
 * \brief Constructor for \ref ssock_write_params.
 */
ssock_write_params::ssock_write_params(ssock* s, const void* b, size_t sz)
    : sock(s)
{
    const uint8_t* in = (const uint8_t*)b;

    buf.reserve(sz);
    copy(in, in + sz, back_inserter(buf));
}

/**
 * \brief Dummy ssock context.
 */
struct dummy_ssock
{
    function<int(ssock*, void*, size_t*)> readfunc;
    function<int(ssock*, const void*, size_t*)> writefunc;
};

/**
 * \brief Initialize a dummy ssock instance for testing.
 * 
 * \param sock      The socket instance to initialize.
 * \param onread    Callback for reads.
 * \param onwrite   Callback for writes.
 *
 * \returns a status code indicating success or failure.
 *      - VCBLOCKCHAIN_STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
int dummy_ssock_init(
    ssock* sock, std::function<int(ssock*, void*, size_t*)> onread,
    std::function<int(ssock*, const void*, size_t*)> onwrite)
{
    sock->hdr.dispose = &dummy_ssock_dispose;
    sock->read = &dummy_ssock_read;
    sock->write = &dummy_ssock_write;
    dummy_ssock* dummy = new dummy_ssock;
    sock->context = dummy;
    dummy->readfunc = onread;
    dummy->writefunc = onwrite;

    return VCBLOCKCHAIN_STATUS_SUCCESS;
}

/**
 * \brief Read callback for dummy sock.
 */
static int dummy_ssock_read(ssock* sock, void* buf, size_t* size)
{
    dummy_ssock* dummy = (dummy_ssock*)sock->context;

    return dummy->readfunc(sock, buf, size);
}

/**
 * \brief Write callback for dummy sock.
 */
static int dummy_ssock_write(ssock* sock, const void* buf, size_t* size)
{
    dummy_ssock* dummy = (dummy_ssock*)sock->context;

    return dummy->writefunc(sock, buf, size);
}

/**
 * \brief Dispose method for dummy sock.
 */
static void dummy_ssock_dispose(void* disp)
{
    ssock* sock = (ssock*)disp;
    dummy_ssock* dummy = (dummy_ssock*)sock->context;

    delete dummy;
}

/**
 * \file test/ssock/dummy_ssock.h
 *
 * Dummy ssock implementation, used for testing.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#ifndef TEST_SSOCK_DUMMY_SSOCK_HEADER_GUARD
#define TEST_SSOCK_DUMMY_SSOCK_HEADER_GUARD

#ifndef __cplusplus
#error This is a C++ only header.
#endif /*__cplusplus*/

#include <functional>
#include <vcblockchain/ssock.h>
#include <vector>

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
    std::function<int(ssock*, const void*, size_t*)> onwrite);

/**
 * \brief Helper structure for checking write parameters from the dummy sock.
 */
struct ssock_write_params
{
    /**
     * \brief Constructor for \ref ssock_write_params.
     */
    ssock_write_params(ssock* s, const void* b, size_t sz);

    ssock* sock;
    std::vector<uint8_t> buf;
};


#endif /*TEST_SSOCK_DUMMY_SSOCK_HEADER_GUARD*/

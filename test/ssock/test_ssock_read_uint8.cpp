/**
 * \file test/ssock/test_ssock_read_uint8.cpp
 *
 * Unit tests for ssock_read_uint8.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <algorithm>
#include <gtest/gtest.h>
#include <list>
#include <memory>
#include <vcblockchain/byteswap.h>
#include <vpr/allocator/malloc_allocator.h>

#include "dummy_ssock.h"

using namespace std;

/**
 * Test that ssock_read_uint8 does runtime parameter checks.
 */
TEST(test_ssock_read_uint8, parameter_checks)
{
    ssock sock;

    /* build a simple dummy socket. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        dummy_ssock_init(
            &sock,
            [&](ssock*, void*, size_t*) -> int {
                return VCBLOCKCHAIN_STATUS_SUCCESS;
            },
            [&](ssock*, const void*, size_t*) -> int {
                return VCBLOCKCHAIN_STATUS_SUCCESS;
            }));

    uint8_t val = 0U;

    /* call with invalid socket. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_read_uint8(nullptr, &val));

    /* call with invalid value pointer. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_read_uint8(&sock, nullptr));

    /* clean up */
    dispose((disposable_t*)&sock);
}

/**
 * Test that ssock_read_uint8 writes a value packet as expected.
 */
TEST(test_ssock_read_uint8, happy_path)
{
    ssock sock;
    list<shared_ptr<vector<uint8_t>>> io_buf;

    /* build a simple dummy socket. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        dummy_ssock_init(
            &sock,
            [&](ssock*, void* b, size_t* sz) -> int {
                shared_ptr<vector<uint8_t>> buf = io_buf.front();
                io_buf.pop_front();

                if (*sz != buf->size())
                    return VCBLOCKCHAIN_ERROR_SSOCK_READ_UNEXPECTED_DATA_SIZE;

                copy(buf->begin(), buf->end(), (uint8_t*)b);

                return VCBLOCKCHAIN_STATUS_SUCCESS;
            },
            [&](ssock*, const void*, size_t*) -> int {
                return VCBLOCKCHAIN_STATUS_SUCCESS;
            }));

    uint8_t EXPECTED_VAL = 10;

    /* create a buffer for the type. */
    auto b1 = make_shared<vector<uint8_t>>();
    b1->push_back(SSOCK_DATA_TYPE_UINT8);
    io_buf.push_back(b1);

    /* create a buffer for the size. */
    auto b2 = make_shared<vector<uint8_t>>();
    b2->push_back(0);
    b2->push_back(0);
    b2->push_back(0);
    b2->push_back(1);
    io_buf.push_back(b2);

    /* create a buffer for the uint8 value. */
    auto b3 = make_shared<vector<uint8_t>>();
    uint8_t buf[1];
    memcpy(buf, &EXPECTED_VAL, 1);
    copy(buf, buf + 1, back_inserter(*b3));
    io_buf.push_back(b3);

    uint8_t val = 0U;

    /* reading a data packet should succeed. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_read_uint8(&sock, &val));

    /* the uint8_t value should be equal to our expected value. */
    EXPECT_EQ(EXPECTED_VAL, val);

    /* clean up */
    dispose((disposable_t*)&sock);
}

/**
 * \file test/sock/test_ssock_methods.cpp
 *
 * Unit tests for public methods for ssock.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <functional>
#include <gtest/gtest.h>
#include <list>
#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <vcblockchain/byteswap.h>
#include <vcblockchain/ssock.h>
#include <vector>
#include <vpr/allocator/malloc_allocator.h>

using namespace std;

/* forward decls. */
static int dummy_ssock_init(
    ssock*, function<int(ssock*, void*, size_t*)>,
    function<int(ssock*, const void*, size_t*)>);
static int dummy_ssock_read(ssock* sock, void* buf, size_t* size);
static int dummy_ssock_write(ssock* sock, const void* buf, size_t* size);
static void dummy_ssock_dispose(void* sock);

struct ssock_write_params
{
    ssock_write_params(ssock* s, const void* b, size_t sz)
        : sock(s)
    {
        const uint8_t* in = (const uint8_t*)b;

        buf.reserve(sz);
        copy(in, in + sz, back_inserter(buf));
    }

    ssock* sock;
    vector<uint8_t> buf;
};

/**
 * Test that the basics of reading and writing work with ssock.
 */
TEST(test_ssock_methods, basics)
{
    ssock sock;
    bool read_called = false;
    ssock* read_sock = nullptr;
    void* read_buf = nullptr;
    size_t* read_size = nullptr;
    bool write_called = false;
    ssock* write_sock = nullptr;
    const void* write_buf = nullptr;
    size_t* write_size = nullptr;

    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        dummy_ssock_init(
            &sock,
            [&](ssock* sock, void* buf, size_t* size) -> int {
                read_called = true;
                read_sock = sock;
                read_buf = buf;
                read_size = size;

                return VCBLOCKCHAIN_STATUS_SUCCESS;
            },
            [&](ssock* sock, const void* buf, size_t* size) -> int {
                write_called = true;
                write_sock = sock;
                write_buf = buf;
                write_size = size;

                return VCBLOCKCHAIN_STATUS_SUCCESS;
            }));

    size_t readin_size = 10;
    int readin_buf = 7;

    /* call read. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_read(&sock, &readin_buf, &readin_size));

    /* verify values were passed correctly to read. */
    EXPECT_TRUE(read_called);
    EXPECT_EQ(&sock, read_sock);
    EXPECT_EQ(&readin_buf, read_buf);
    EXPECT_EQ(&readin_size, read_size);

    size_t writein_size = 19;
    int writein_buf = 2;

    /* call read. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_write(&sock, &writein_buf, &writein_size));

    /* verify values were passed correctly to write. */
    EXPECT_TRUE(write_called);
    EXPECT_EQ(&sock, write_sock);
    EXPECT_EQ(&writein_buf, write_buf);
    EXPECT_EQ(&writein_size, write_size);

    /* cleanup */
    dispose((disposable_t*)&sock);
}

TEST(test_ssock_methods, posix_socket)
{
    const uint64_t EXPECTED_VALUE = 88229;
    int sv[2];
    ssock lhs, rhs;

    /* build a socket pair. */
    ASSERT_EQ(0, socketpair(AF_UNIX, SOCK_STREAM, 0, sv));

    /* create the lhs socket. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS, ssock_init_from_posix(&lhs, sv[0]));

    /* create the rhs socket. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS, ssock_init_from_posix(&rhs, sv[1]));

    /* write the expected value to lhs. */
    size_t write_bytes = sizeof(EXPECTED_VALUE);
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_write(&lhs, &EXPECTED_VALUE, &write_bytes));

    /* the number of bytes written should be correct. */
    EXPECT_EQ(sizeof(EXPECTED_VALUE), write_bytes);

    /* read the expected value from rhs. */
    uint64_t intval = 0;
    size_t read_bytes = sizeof(EXPECTED_VALUE);
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_read(&rhs, &intval, &read_bytes));

    /* the number of read bytes should match. */
    EXPECT_EQ(sizeof(EXPECTED_VALUE), read_bytes);
    /* the read value should match our expected value. */
    EXPECT_EQ(EXPECTED_VALUE, intval);

    /* clean up. */
    dispose((disposable_t*)&lhs);
    dispose((disposable_t*)&rhs);
}

/**
 * Test that ssock_write_data does runtime parameter checks.
 */
TEST(test_ssock_methods, ssock_write_data_parameter_checks)
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

    int val = 10;

    /* call with invalid socket. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_write_data(nullptr, &val, sizeof(val)));

    /* call with invalid val pointer. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_write_data(&sock, nullptr, sizeof(val)));

    /* clean up */
    dispose((disposable_t*)&sock);
}

/**
 * Test that ssock_write_data writes a data packet as expected.
 */
TEST(test_ssock_methods, ssock_write_data_happy_path)
{
    ssock sock;
    vector<shared_ptr<ssock_write_params>> write_calls;

    /* build a simple dummy socket. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        dummy_ssock_init(
            &sock,
            [&](ssock*, void*, size_t*) -> int {
                return VCBLOCKCHAIN_STATUS_SUCCESS;
            },
            [&](ssock* sock, const void* val, size_t* size) -> int {
                write_calls.push_back(
                    make_shared<ssock_write_params>(
                        sock, val, *size));

                return VCBLOCKCHAIN_STATUS_SUCCESS;
            }));

    int val = 10;

    /* writing a data packet should succeed. */
    EXPECT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_write_data(&sock, &val, sizeof(val)));

    /* the internal write method should have been called three times. */
    ASSERT_EQ(3U, write_calls.size());

    /* the socket is the first argument. */
    EXPECT_EQ(&sock, write_calls[0]->sock);

    /* the first buffer contains the data type. */
    ASSERT_EQ(sizeof(uint8_t), write_calls[0]->buf.size());
    EXPECT_EQ(SSOCK_DATA_TYPE_DATA_PACKET, write_calls[0]->buf[0]);

    /* the second buffer contains the size. */
    ASSERT_EQ(sizeof(uint32_t), write_calls[1]->buf.size());
    uint32_t net_size;
    memcpy(&net_size, &write_calls[1]->buf[0], sizeof(net_size));
    EXPECT_EQ(sizeof(val), (size_t)ntohl(net_size));

    /* the third buffer contains the data. */
    ASSERT_EQ(sizeof(val), write_calls[2]->buf.size());
    int v2;
    memcpy(&v2, &write_calls[2]->buf[0], sizeof(v2));
    EXPECT_EQ(val, v2);

    /* clean up */
    dispose((disposable_t*)&sock);
}

/**
 * Test that ssock_read_data does runtime parameter checks.
 */
TEST(test_ssock_methods, ssock_read_data_parameter_checks)
{
    ssock sock;
    allocator_options_t alloc_opts;

    /* create malloc allocator. */
    malloc_allocator_options_init(&alloc_opts);

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

    void* val = nullptr;
    uint32_t size = 0U;

    /* call with invalid socket. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_read_data(nullptr, &alloc_opts, &val, &size));

    /* call with invalid alloc_opts. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_read_data(&sock, nullptr, &val, &size));

    /* call with invalid value buffer pointer. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_read_data(&sock, &alloc_opts, nullptr, &size));

    /* call with invalid size pointer. */
    EXPECT_EQ(VCBLOCKCHAIN_ERROR_INVALID_ARG,
        ssock_read_data(&sock, &alloc_opts, &val, nullptr));

    /* clean up */
    dispose((disposable_t*)&sock);
    dispose((disposable_t*)&alloc_opts);
}

/**
 * Test that ssock_read_data writes a data packet as expected.
 */
TEST(test_ssock_methods, ssock_read_data_happy_path)
{
    ssock sock;
    list<shared_ptr<vector<uint8_t>>> io_buf;
    allocator_options_t alloc_opts;

    /* create malloc allocator. */
    malloc_allocator_options_init(&alloc_opts);

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

    int32_t EXPECTED_VAL = 10;

    /* create a buffer for the type. */
    auto b1 = make_shared<vector<uint8_t>>();
    b1->push_back(SSOCK_DATA_TYPE_DATA_PACKET);
    io_buf.push_back(b1);

    /* create a buffer for the size. */
    auto b2 = make_shared<vector<uint8_t>>();
    b2->push_back(0);
    b2->push_back(0);
    b2->push_back(0);
    b2->push_back(4);
    io_buf.push_back(b2);

    /* create a buffer for the int value. */
    auto b3 = make_shared<vector<uint8_t>>();
    b3->push_back(10);
    b3->push_back(0);
    b3->push_back(0);
    b3->push_back(0);
    io_buf.push_back(b3);

    void* val = nullptr;
    uint32_t size;

    /* reading a data packet should succeed. */
    ASSERT_EQ(VCBLOCKCHAIN_STATUS_SUCCESS,
        ssock_read_data(&sock, &alloc_opts, &val, &size));

    /* the size of the data packet should be the same as our expected val. */
    ASSERT_EQ(sizeof(EXPECTED_VAL), size);
    /* the value should not be null. */
    ASSERT_NE(nullptr, val);

    /* the int32_t value should be equal to our expected value. */
    EXPECT_EQ(EXPECTED_VAL, *((int32_t*)val));

    /* clean up */
    dispose((disposable_t*)&sock);
    release(&alloc_opts, val);
    dispose((disposable_t*)&alloc_opts);
}

struct dummy_ssock
{
    function<int(ssock*, void*, size_t*)> readfunc;
    function<int(ssock*, const void*, size_t*)> writefunc;
};

/**
 * \brief Create a dummy ssock instance for testing.
 */
static int dummy_ssock_init(
    ssock* sock, function<int(ssock*, void*, size_t*)> readfunc,
    function<int(ssock*, const void*, size_t*)> writefunc)
{
    sock->hdr.dispose = &dummy_ssock_dispose;
    sock->read = &dummy_ssock_read;
    sock->write = &dummy_ssock_write;
    dummy_ssock* dummy = new dummy_ssock;
    sock->context = dummy;
    dummy->readfunc = readfunc;
    dummy->writefunc = writefunc;

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

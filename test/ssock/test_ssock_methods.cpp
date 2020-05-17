/**
 * \file test/sock/test_ssock_methods.cpp
 *
 * Unit tests for public methods for ssock.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#include <functional>
#include <gtest/gtest.h>
#include <vcblockchain/ssock.h>
#include <sys/socket.h>
#include <sys/types.h>

using namespace std;

/* forward decls. */
static int dummy_ssock_init(
    ssock*, function<int(ssock*, void*, size_t*)>,
    function<int(ssock*, const void*, size_t*)>);
static int dummy_ssock_read(ssock* sock, void* buf, size_t* size);
static int dummy_ssock_write(ssock* sock, const void* buf, size_t* size);
static void dummy_ssock_dispose(void* sock);

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

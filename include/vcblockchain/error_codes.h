/**
 * \file vcblockchain/error_codes.h
 *
 * \brief Error codes for vcblockchain.
 *
 * \copyright 2020 Velo Payments, Inc.  All rights reserved.
 */

#ifndef VCBLOCKCHAIN_ERROR_CODES_HEADER_GUARD
#define VCBLOCKCHAIN_ERROR_CODES_HEADER_GUARD

/* make this header C++ friendly. */
#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/**
 * \defgroup VCBlockchainErrorCodes Error codes for the Velo C Blockchain
 * Library.
 *
 * @{
 */

/**
 * \brief The \ref VCBLOCKCHAIN_STATUS_SUCCESS code represents the successful
 * completion of a Velo C Blockchain Library method.
 */
#define VCBLOCKCHAIN_STATUS_SUCCESS 0x0000

/**
 * \brief An attempt was made to call a vcblockchain method with an invalid
 * argument.
 */
#define VCBLOCKCHAIN_ERROR_INVALID_ARG 0x5100

/**
 * \brief An error occurred when attempting to read from an ssock instance.
 */
#define VCBLOCKCHAIN_ERROR_SSOCK_READ 0x5101

/**
 * \brief An error occurred when attempting to write to an ssock instance.
 */
#define VCBLOCKCHAIN_ERROR_SSOCK_WRITE 0x5102

/**
 * @}
 */

/* make this header C++ friendly. */
#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*VCBLOCKCHAIN_ERROR_CODES_HEADER_GUARD*/

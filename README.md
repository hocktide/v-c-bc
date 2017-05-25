Velo C Blockchain Library
=========================

The Velo C Blockchain Library is a low-level C library that provides interfaces
and implementations for blockchain level services, such as entity creation,
mutual authentication, blockchain bootstrapping, block creation, and block
verification.

Building
========

The [`vc-toolchain`][vc-toolchain-url] project needs to be installed in the
`/opt/vctoolchain` subdirectory.  If a different installation directory is used,
then the `TOOLCHAIN_DIR` environment variable should be set to that directory
instead.  The [Velo Portable Runtime][vpr-url], [Velo C Crypto][vccrypt-url],
and [Velo C Certificate][vccert-url] libraries are required to link against this
library and to run the test cases.

[vc-toolchain-url]: https://github.com/VeloPayments/vc-toolchain
[vpr-url]: https://github.com/VeloPayments/vpr
[vccrypt-url]: https://github.com/VeloPayments/vccrypt
[vccert-url]: https://github.com/VeloPayments/vccert

The default build target will just build the vcblockchain release library for
each supported platform.  To run unit tests, use the `test` build target.  This
will build both the release and the checked libraries for the current host.  The
`test` build target depends on Google Test.  The location of the Google Test
source distribution must be included in the `GTEST_DIR` environment variable.
For instance:

    #build just the release libraries
    make

    #build with unit tests - also builds checked libraries
    GTEST_DIR="path/to/google/test" make test

The resulting library will be available under the `build` subdirectory, which
will be created as part of the build process.

LIB_NAME=libvcblockchain.a
BUILD_DIR=$(CURDIR)/build
HOST_CHECKED_BUILD_DIR=$(BUILD_DIR)/host/checked

#vpr options
VPR_DIR?=$(CURDIR)/lib/vpr
VPR_INCLUDE_PATH?=$(VPR_DIR)/include
VPR_CFLAGS=-I $(VPR_INCLUDE_PATH)
VPR_HOST_CHECKED_LIB_DIR?=$(VPR_DIR)/build/host/checked
VPR_HOST_RELEASE_LIB_DIR?=$(VPR_DIR)/build/host/release
VPR_CORTEXMSOFT_RELEASE_LIB_DIR?=$(VPR_DIR)/build/cortex-m4-softfp/release
VPR_CORTEXMHARD_RELEASE_LIB_DIR?=$(VPR_DIR)/build/cortex-m4-hardfp/release
VPR_HOST_CHECKED_LIB?=$(VPR_HOST_CHECKED_LIB_DIR)/libvpr.a
VPR_HOST_RELEASE_LIB?=$(VPR_HOST_RELEASE_LIB_DIR)/libvpr.a
VPR_CORTEXMSOFT_RELEASE_LIB?=$(VPR_CORTEXMSOFT_RELEASE_LIB_DIR)/libvpr.a
VPR_CORTEXMHARD_RELEASE_LIB?=$(VPR_CORTEXMHARD_RELEASE_LIB_DIR)/libvpr.a
VPR_HOST_CHECKED_LINK?=-L $(VPR_HOST_CHECKED_LIB_DIR) -lvpr
VPR_HOST_RELEASE_LINK?=-L $(VPR_HOST_RELEASE_LIB_DIR) -lvpr

#vccrypt options
VCCRYPT_DIR?=$(CURDIR)/lib/vccrypt
VCCRYPT_INCLUDE_PATH?=$(VCCRYPT_DIR)/include
VCCRYPT_CFLAGS=-I $(VCCRYPT_INCLUDE_PATH)
VCCRYPT_HOST_CHECKED_LIB_DIR?=$(VCCRYPT_DIR)/build/host/checked
VCCRYPT_HOST_RELEASE_LIB_DIR?=$(VCCRYPT_DIR)/build/host/release
VCCRYPT_CORTEXMSOFT_RELEASE_LIB_DIR?=\
    $(VCCRYPT_DIR)/build/cortex-m4-softfp/release
VCCRYPT_CORTEXMHARD_RELEASE_LIB_DIR?=\
    $(VCCRYPT_DIR)/build/cortex-m4-hardfp/release
VCCRYPT_HOST_CHECKED_LIB?=$(VCCRYPT_HOST_CHECKED_LIB_DIR)/libvccrypt.a
VCCRYPT_HOST_RELEASE_LIB?=$(VCCRYPT_HOST_RELEASE_LIB_DIR)/libvccrypt.a
VCCRYPT_CORTEXMSOFT_RELEASE_LIB?=\
    $(VCCRYPT_CORTEXMSOFT_RELEASE_LIB_DIR)/libvccrypt.a
VCCRYPT_CORTEXMHARD_RELEASE_LIB?=\
    $(VCCRYPT_CORTEXMHARD_RELEASE_LIB_DIR)/libvccrypt.a
VCCRYPT_HOST_CHECKED_LINK?=-L $(VCCRYPT_HOST_CHECKED_LIB_DIR) -lvccrypt
VCCRYPT_HOST_RELEASE_LINK?=-L $(VCCRYPT_HOST_RELEASE_LIB_DIR) -lvccrypt

#vccert options
VCCERT_DIR?=$(CURDIR)/lib/vccert
VCCERT_INCLUDE_PATH?=$(VCCERT_DIR)/include
VCCERT_CFLAGS=-I $(VCCERT_INCLUDE_PATH)
VCCERT_HOST_CHECKED_LIB_DIR?=$(VCCERT_DIR)/build/host/checked
VCCERT_HOST_RELEASE_LIB_DIR?=$(VCCERT_DIR)/build/host/release
VCCERT_CORTEXMSOFT_RELEASE_LIB_DIR?=$(VCCERT_DIR)/build/cortex-m4-softfp/release
VCCERT_CORTEXMHARD_RELEASE_LIB_DIR?=$(VCCERT_DIR)/build/cortex-m4-hardfp/release
VCCERT_HOST_CHECKED_LIB?=$(VCCERT_HOST_CHECKED_LIB_DIR)/libvccert.a
VCCERT_HOST_RELEASE_LIB?=$(VCCERT_HOST_RELEASE_LIB_DIR)/libvccert.a
VCCERT_CORTEXMSOFT_RELEASE_LIB?=\
    $(VCCERT_CORTEXMSOFT_RELEASE_LIB_DIR)/libvccert.a
VCCERT_CORTEXMHARD_RELEASE_LIB?=\
    $(VCCERT_CORTEXMHARD_RELEASE_LIB_DIR)/libvccert.a
VCCERT_HOST_CHECKED_LINK?=-L $(VCCERT_HOST_CHECKED_LIB_DIR) -lvccert
VCCERT_HOST_RELEASE_LINK?=-L $(VCCERT_HOST_RELEASE_LIB_DIR) -lvccert

#vcdb options
VCDB_DIR?=$(CURDIR)/lib/vcdb
VCDB_INCLUDE_PATH?=$(VCDB_DIR)/include
VCDB_CFLAGS=-I $(VCDB_INCLUDE_PATH)
VCDB_HOST_CHECKED_LIB_DIR?=$(VCDB_DIR)/build/host/checked
VCDB_HOST_RELEASE_LIB_DIR?=$(VCDB_DIR)/build/host/release
VCDB_HOST_CHECKED_LIB?=$(VCDB_HOST_CHECKED_LIB_DIR)/libvcdb.a
VCDB_HOST_RELEASE_LIB?=$(VCDB_HOST_RELEASE_LIB_DIR)/libvcdb.a
VCDB_HOST_CHECKED_LINK?=-L $(VCDB_HOST_CHECKED_LIB_DIR) -lvcdb
VCDB_HOST_RELEASE_LINK?=-L $(VCDB_HOST_RELEASE_LIB_DIR) -lvcdb

#lmdb options
LMDB_DIR?=$(CURDIR)/lib/lmdb
LMDB_INCLUDE_PATH=$(LMDB_DIR)
LMDB_CFLAGS=-I $(LMDB_INCLUDE_PATH)
LMDB_HOST_RELEASE_LIB_DIR?=$(LMDB_DIR)
LMDB_HOST_RELEASE_LIB?=$(LMDB_HOST_RELEASE_LIB_DIR)/liblmdb.a
LMDB_HOST_RELEASE_LINK?=-L $(LMDB_HOST_RELEASE_LIB_DIR) -llmdb

#libevent options
LIBEVENT_DIR?=$(CURDIR)/lib/libevent
LIBEVENT_INCLUDE_PATH=$(LIBEVENT_DIR)
LIBEVENT_CFLAGS=-I $(LIBEVENT_INCLUDE_PATH)
LIBEVENT_HOST_RELEASE_LIB_DIR?=$(LIBEVENT_DIR)/.libs
LIBEVENT_HOST_RELEASE_LIB?=$(LIBEVENT_HOST_RELEASE_LIB_DIR)/libevent.a
LIBEVENT_HOST_RELEASE_LINK?=-L $(LIBEVENT_HOST_RELEASE_LIB_DIR) -levent

#model check options
MODEL_CHECK_DIR?=$(CURDIR)/lib/vcmodel
include $(MODEL_CHECK_DIR)/model_check.mk

#Openbsd compat
PWD?=$(CURDIR)

#library source files
SRCDIR=$(PWD)/src
DIRS=$(SRCDIR) $(SRCDIR)/authentication
SOURCES=$(foreach d,$(DIRS),$(wildcard $(d)/*.c))
STRIPPED_SOURCES=$(patsubst $(SRCDIR)/%,%,$(SOURCES))

#library test files
TESTDIR=$(PWD)/test
TESTDIRS=$(TESTDIR) $(TESTDIR)/authentication
TEST_BUILD_DIR=$(HOST_CHECKED_BUILD_DIR)/test
TEST_DIRS=$(filter-out $(TESTDIR), \
    $(patsubst $(TESTDIR)/%,$(TEST_BUILD_DIR)/%,$(TESTDIRS)))
TEST_SOURCES=$(foreach d,$(TESTDIRS),$(wildcard $(d)/*.cpp))
STRIPPED_TEST_SOURCES=$(patsubst $(TESTDIR)/%,%,$(TEST_SOURCES))
TEST_OBJECTS=$(patsubst %.cpp,$(TEST_BUILD_DIR)/%.o,$(STRIPPED_TEST_SOURCES))
TESTLIBVCBLOCKCHAIN=$(HOST_CHECKED_BUILD_DIR)/testlibvcblockchain

#platform options
CORTEXMSOFT_RELEASE_BUILD_DIR=$(BUILD_DIR)/cortex-m4-softfp/release
CORTEXMSOFT_RELEASE_LIB=$(CORTEXMSOFT_RELEASE_BUILD_DIR)/$(LIB_NAME)
CORTEXMSOFT_RELEASE_DIRS=$(filter-out $(SRCDIR), \
    $(patsubst $(SRCDIR)/%,$(CORTEXMSOFT_RELEASE_BUILD_DIR)/%,$(DIRS)))
CORTEXMSOFT_RELEASE_OBJECTS= \
    $(patsubst %.c,$(CORTEXMSOFT_RELEASE_BUILD_DIR)/%.o,$(STRIPPED_SOURCES))
CORTEXMHARD_RELEASE_BUILD_DIR=$(BUILD_DIR)/cortex-m4-hardfp/release
CORTEXMHARD_RELEASE_LIB=$(CORTEXMHARD_RELEASE_BUILD_DIR)/$(LIB_NAME)
CORTEXMHARD_RELEASE_DIRS=$(filter-out $(SRCDIR), \
    $(patsubst $(SRCDIR)/%,$(CORTEXMHARD_RELEASE_BUILD_DIR)/%,$(DIRS)))
CORTEXMHARD_RELEASE_OBJECTS= \
    $(patsubst %.c,$(CORTEXMHARD_RELEASE_BUILD_DIR)/%.o,$(STRIPPED_SOURCES))
HOST_CHECKED_LIB=$(HOST_CHECKED_BUILD_DIR)/$(LIB_NAME)
HOST_CHECKED_DIRS=$(filter-out $(SRCDIR), \
    $(patsubst $(SRCDIR)/%,$(HOST_CHECKED_BUILD_DIR)/%,$(DIRS)))
HOST_CHECKED_OBJECTS= \
    $(patsubst %.c,$(HOST_CHECKED_BUILD_DIR)/%.o,$(STRIPPED_SOURCES))
HOST_RELEASE_BUILD_DIR=$(BUILD_DIR)/host/release
HOST_RELEASE_LIB=$(HOST_RELEASE_BUILD_DIR)/$(LIB_NAME)
HOST_RELEASE_DIRS=$(filter-out $(SRCDIR), \
    $(patsubst $(SRCDIR)/%,$(HOST_RELEASE_BUILD_DIR)/%,$(DIRS)))
HOST_RELEASE_OBJECTS= \
    $(patsubst %.c,$(HOST_RELEASE_BUILD_DIR)/%.o,$(STRIPPED_SOURCES))

#Dependencies
GTEST_DIR?=$(PWD)/lib/googletest/googletest
GTEST_OBJ=$(TEST_BUILD_DIR)/gtest-all.o

#Toolchain location
TOOLCHAIN_DIR?=/opt/vctoolchain

#compilers
HOST_CHECKED_CC=$(TOOLCHAIN_DIR)/host/bin/gcc
HOST_CHECKED_CXX=$(TOOLCHAIN_DIR)/host/bin/g++
HOST_CHECKED_AR=$(AR)
HOST_CHECKED_RANLIB=$(RANLIB)
HOST_RELEASE_CC=$(TOOLCHAIN_DIR)/host/bin/gcc
HOST_RELEASE_CXX=$(TOOLCHAIN_DIR)/host/bin/g++
HOST_RELEASE_AR=$(AR)
HOST_RELEASE_RANLIB=$(RANLIB)
CORTEXMSOFT_RELEASE_CC=$(TOOLCHAIN_DIR)/cortex-m4-softfp/bin/arm-none-eabi-gcc
CORTEXMSOFT_RELEASE_CXX=$(TOOLCHAIN_DIR)/cortex-m4-softfp/bin/arm-none-eabi-g++
CORTEXMSOFT_RELEASE_AR=$(TOOLCHAIN_DIR)/cortex-m4-softfp/bin/arm-none-eabi-ar
CORTEXMSOFT_RELEASE_RANLIB=$(TOOLCHAIN_DIR)/cortex-m4-softfp/bin/arm-none-eabi-ranlib
CORTEXMHARD_RELEASE_CC=$(TOOLCHAIN_DIR)/cortex-m4-hardfp/bin/arm-none-eabi-gcc
CORTEXMHARD_RELEASE_CXX=$(TOOLCHAIN_DIR)/cortex-m4-hardfp/bin/arm-none-eabi-g++
CORTEXMHARD_RELEASE_AR=$(TOOLCHAIN_DIR)/cortex-m4-hardfp/bin/arm-none-eabi-ar
CORTEXMHARD_RELEASE_RANLIB=$(TOOLCHAIN_DIR)/cortex-m4-hardfp/bin/arm-none-eabi-ranlib

#platform compiler flags
COMMON_INCLUDES=$(MODEL_CHECK_INCLUDES) $(VPR_CFLAGS) $(VCCRYPT_CFLAGS) \
                -I $(PWD)/include
COMMON_CFLAGS=$(COMMON_INCLUDES) -Wall -Werror -Wextra
HOST_CHECKED_CFLAGS=$(COMMON_CFLAGS) -fPIC -O0 -fprofile-arcs -ftest-coverage
HOST_RELEASE_CFLAGS=$(COMMON_CFLAGS) -fPIC -O2
COMMON_CXXFLAGS=-I $(PWD)/include -Wall -Werror -Wextra
HOST_CHECKED_CXXFLAGS=-std=c++14 $(COMMON_CXXFLAGS) -O0 -fprofile-arcs \
    -ftest-coverage
HOST_RELEASE_CXXFLAGS=-std=c++14 $(COMMON_CXXFLAGS) -O2
TEST_CXXFLAGS=$(HOST_RELEASE_CXXFLAGS) $(COMMON_INCLUDES) -I $(GTEST_DIR) \
     -I $(GTEST_DIR)/include
CORTEXMSOFT_RELEASE_CFLAGS=-std=gnu99 $(COMMON_CFLAGS) -O2 -mcpu=cortex-m4 \
    -mfloat-abi=soft -mthumb -fno-common -ffunction-sections -fdata-sections \
    -ffreestanding -fno-builtin -mapcs
CORTEXMSOFT_RELEASE_CXXFLAGS=-std=gnu++14 $(COMMON_CXXFLAGS) -O2 \
    -mcpu=cortex-m4 -mfloat-abi=soft -mthumb -fno-common -ffunction-sections \
    -fdata-sections -ffreestanding -fno-builtin -mapcs
CORTEXMHARD_RELEASE_CFLAGS=-std=gnu99 $(COMMON_CFLAGS) -O2 -mcpu=cortex-m4 \
    -mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -fno-common -ffunction-sections \
    -fdata-sections -ffreestanding -fno-builtin -mapcs
CORTEXMHARD_RELEASE_CXXFLAGS=-std=gnu++14 $(COMMON_CXXFLAGS) -O2 \
    -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -fno-common \
    -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mapcs

#phony targets
.PHONY: ALL clean test host.lib.checked host.lib.release cortexmsoft.lib.release
.PHONY: cortexmhard.lib.release libdepends test.libdepends clean.libdepends
.PHONY: build.lib.vpr build.lib.vccrypt build.lib.vccert build.lib.vcdb
.PHONY: build.lib.lmdb
.PHONY: test.lib.vpr test.lib.vccrypt test.lib.vccert test.lib.vcdb
.PHONY: test.lib.lmdb
.PHONY: clean.lib.vpr clean.lib.vccrypt clean.lib.vccert clean.lib.vcdb
.PHONY: extract.lib
.PHONY: extract.lib.vpr extract.lib.vccrypt extract.lib.vccert extract.lib.vcdb

#main build target
ALL: host.lib.checked host.lib.release cortexmsoft.lib.release
ALL: cortexmhard.lib.release

libdepends: build.lib.vpr build.lib.vccrypt build.lib.vccert build.lib.vcdb
libdepends: build.lib.lmdb build.lib.libevent
build.lib.vccrypt: build.lib.vpr
build.lib.vccert: build.lib.vccrypt
build.lib.vcdb: build.lib.vpr
test.libdepends: libdepends
test.libdepends: test.lib.vpr test.lib.vccrypt test.lib.vccert test.lib.vcdb
test.libdepends: test.lib.lmdb
test.lib.vpr: build.lib.vpr
test.lib.vccrypt: build.lib.vpr build.lib.vccrypt
test.lib.vccert: build.lib.vpr build.lib.vccrypt build.lib.vccert
test.lib.vcdb: build.lib.vpr build.lib.vcdb
test.lib.lmdb: build.lib.lmdb
test.lib.libevent: build.lib.libevent
clean.libdepends: clean.lib.vpr clean.lib.vccrypt clean.lib.vccert
clean.libdepends: clean.lib.vcdb clean.lib.lmdb clean.lib.libevent

extract.lib: libdepends
extract.lib: extract.lib.vpr extract.lib.vccrypt extract.lib.vccert
extract.lib: extract.lib.vcdb extract.lib.lmdb extract.lib.libevent

$(LIBEVENT_DIR)/Makefile:
	(cd $(LIBEVENT_DIR) && \
	    ./configure --disable-libevent-install --disable-openssl)

build.lib.vpr:
	(cd lib/vpr && $(MAKE))

build.lib.vccrypt:
	(cd lib/vccrypt && $(MAKE))

build.lib.vccert:
	(cd lib/vccert && $(MAKE))

build.lib.vcdb:
	(cd lib/vcdb && $(MAKE))

build.lib.lmdb:
	(cd lib/lmdb && $(MAKE))

build.lib.libevent: $(LIBEVENT_DIR)/Makefile
	(cd $(LIBEVENT_DIR) && $(MAKE))

test.lib.vpr:
	(cd lib/vpr && $(MAKE) test)

test.lib.vccrypt:
	(cd lib/vccrypt && $(MAKE) test)

test.lib.vccert:
	(cd lib/vccert && $(MAKE) test)

test.lib.vcdb:
	(cd lib/vcdb && $(MAKE) test)

test.lib.lmdb:
	(cd lib/lmdb && $(MAKE) test)

test.lib.libevent:
	(cd $(LIBEVENT_DIR) && $(MAKE) test)

clean.lib.vpr:
	(cd lib/vpr && $(MAKE) clean)

clean.lib.vccrypt:
	(cd lib/vccrypt && $(MAKE) clean)

clean.lib.vccert:
	(cd lib/vccert && $(MAKE) clean)

clean.lib.vcdb:
	(cd lib/vcdb && $(MAKE) clean)

clean.lib.lmdb:
	(cd lib/lmdb && $(MAKE) clean)

clean.lib.libevent: $(LIBEVENT_DIR)/Makefile
	(cd $(LIBEVENT_DIR) && $(MAKE) clean)

#host targets
host.lib.checked: libdepends $(HOST_CHECKED_DIRS) $(HOST_CHECKED_LIB)
host.lib.release: libdepends $(HOST_RELEASE_DIRS) $(HOST_RELEASE_LIB)

#cortex M4 soft floating point targets
cortexmsoft.lib.release: libdepends
cortexmsoft.lib.release: $(CORTEXMSOFT_RELEASE_DIRS) $(CORTEXMSOFT_RELEASE_LIB)

#cortex M4F hard floating point targets
cortexmhard.lib.release: libdepends
cortexmhard.lib.release: $(CORTEXMHARD_RELEASE_DIRS) $(CORTEXMHARD_RELEASE_LIB)

#build missing directories
$(HOST_CHECKED_DIRS) $(HOST_RELEASE_DIRS) $(TEST_DIRS):
	mkdir -p $@
$(CORTEXMSOFT_RELEASE_DIRS) $(CORTEXMHARD_RELEASE_DIRS):
	mkdir -p $@

#Checked library (used for testing)
$(HOST_CHECKED_LIB) : libdepends extract.lib
$(HOST_CHECKED_LIB) : $(HOST_CHECKED_OBJECTS)
	$(AR) rcs $@ $(HOST_CHECKED_OBJECTS) \
		$(dir $(HOST_CHECKED_LIB))/libdepends/vpr/*.o \
		$(dir $(HOST_CHECKED_LIB))/libdepends/vccrypt/*.o \
		$(dir $(HOST_CHECKED_LIB))/libdepends/vccert/*.o \
		$(dir $(HOST_CHECKED_LIB))/libdepends/vcdb/*.o \
		$(dir $(HOST_CHECKED_LIB))/libdepends/lmdb/*.o \
		$(dir $(HOST_CHECKED_LIB))/libdepends/libevent/*.o

#Host release library
$(HOST_RELEASE_LIB) : libdepends extract.lib
$(HOST_RELEASE_LIB) : $(HOST_RELEASE_OBJECTS)
	$(AR) rcs $@ $(HOST_RELEASE_OBJECTS) \
		$(dir $(HOST_RELEASE_LIB))/libdepends/vpr/*.o \
		$(dir $(HOST_RELEASE_LIB))/libdepends/vccrypt/*.o \
		$(dir $(HOST_RELEASE_LIB))/libdepends/vccert/*.o \
		$(dir $(HOST_RELEASE_LIB))/libdepends/vcdb/*.o \
		$(dir $(HOST_RELEASE_LIB))/libdepends/lmdb/*.o \
		$(dir $(HOST_RELEASE_LIB))/libdepends/libevent/*.o

#Cortex-M4 softfp library
$(CORTEXMSOFT_RELEASE_LIB) : libdepends extract.lib
$(CORTEXMSOFT_RELEASE_LIB) : $(CORTEXMSOFT_RELEASE_OBJECTS)
	$(CORTEXMSOFT_RELEASE_AR) rcs $@ $(CORTEXMSOFT_RELEASE_OBJECTS) \
		$(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vpr/*.o \
		$(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vccrypt/*.o \
		$(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vccert/*.o

#Cortex-M4 hardfp library
$(CORTEXMHARD_RELEASE_LIB) : libdepends extract.lib
$(CORTEXMHARD_RELEASE_LIB) : $(CORTEXMHARD_RELEASE_OBJECTS)
	$(CORTEXMHARD_RELEASE_AR) rcs $@ $(CORTEXMHARD_RELEASE_OBJECTS) \
		$(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vpr/*.o \
		$(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vccrypt/*.o \
		$(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vccert/*.o

#Google Test object
$(GTEST_OBJ): $(GTEST_DIR)/src/gtest-all.cc
	mkdir -p $(dir $@)
	$(HOST_RELEASE_CXX) $(TEST_CXXFLAGS) -c -o $@ $<

#Test build objects
$(TEST_BUILD_DIR)/%.o: $(TESTDIR)/%.cpp
	mkdir -p $(dir $@)
	$(HOST_RELEASE_CXX) $(TEST_CXXFLAGS) -c -o $@ $<

#Host checked build objects
$(HOST_CHECKED_BUILD_DIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(HOST_CHECKED_CC) $(HOST_CHECKED_CFLAGS) -c -o $@ $<

#Host release build objects
$(HOST_RELEASE_BUILD_DIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(HOST_RELEASE_CC) $(HOST_RELEASE_CFLAGS) -c -o $@ $<

#Cortex-M soft float release build objects
$(CORTEXMSOFT_RELEASE_BUILD_DIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CORTEXMSOFT_RELEASE_CC) $(CORTEXMSOFT_RELEASE_CFLAGS) -c -o $@ $<

#Cortex-M hard float release build objects
$(CORTEXMHARD_RELEASE_BUILD_DIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(dir $@)
	$(CORTEXMHARD_RELEASE_CC) $(CORTEXMHARD_RELEASE_CFLAGS) -c -o $@ $<

test: test.libdepends $(TEST_DIRS) host.lib.checked $(TESTLIBVCBLOCKCHAIN)
	LD_LIBRARY_PATH=$(TOOLCHAIN_DIR)/host/lib:$(TOOLCHAIN_DIR)/host/lib64:$(LD_LIBRARY_PATH) $(TESTLIBVCBLOCKCHAIN)

clean: clean.libdepends
	rm -rf $(BUILD_DIR)

$(TESTLIBVCBLOCKCHAIN): libdepends
$(TESTLIBVCBLOCKCHAIN): $(HOST_CHECKED_OBJECTS) $(TEST_OBJECTS) $(GTEST_OBJ)
	find $(TEST_BUILD_DIR) -name "*.gcda" -exec rm {} \; -print
	rm -f gtest-all.gcda
	$(HOST_RELEASE_CXX) $(TEST_CXXFLAGS) -fprofile-arcs \
	    -o $@ $(TEST_OBJECTS) \
	    $(HOST_CHECKED_OBJECTS) $(GTEST_OBJ) -lpthread \
	    -L $(TOOLCHAIN_DIR)/host/lib64 -lstdc++ \
	    $(VCCRYPT_HOST_RELEASE_LINK) $(VPR_HOST_RELEASE_LINK)

extract.lib.vpr: libdepends
extract.lib.vpr:
	mkdir -p $(dir $(HOST_CHECKED_LIB))/libdepends/vpr
	(cd $(dir $(HOST_CHECKED_LIB))/libdepends/vpr \
	    && $(HOST_CHECKED_AR) -x $(VPR_HOST_CHECKED_LIB))
	mkdir -p $(dir $(HOST_RELEASE_LIB))/libdepends/vpr
	(cd $(dir $(HOST_RELEASE_LIB))/libdepends/vpr \
	    && $(HOST_RELEASE_AR) -x $(VPR_HOST_RELEASE_LIB))
	mkdir -p $(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vpr
	(cd $(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vpr \
	    && $(CORTEXMSOFT_RELEASE_AR) -x $(VPR_CORTEXMSOFT_RELEASE_LIB))
	mkdir -p $(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vpr
	(cd $(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vpr \
	    && $(CORTEXMHARD_RELEASE_AR) -x $(VPR_CORTEXMHARD_RELEASE_LIB))

extract.lib.vccrypt: libdepends
extract.lib.vccrypt:
	mkdir -p $(dir $(HOST_CHECKED_LIB))/libdepends/vccrypt
	(cd $(dir $(HOST_CHECKED_LIB))/libdepends/vccrypt \
	    && $(HOST_CHECKED_AR) -x $(VCCRYPT_HOST_CHECKED_LIB))
	mkdir -p $(dir $(HOST_RELEASE_LIB))/libdepends/vccrypt
	(cd $(dir $(HOST_RELEASE_LIB))/libdepends/vccrypt \
	    && $(HOST_RELEASE_AR) -x $(VCCRYPT_HOST_RELEASE_LIB))
	mkdir -p $(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vccrypt
	(cd $(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vccrypt \
	    && $(CORTEXMSOFT_RELEASE_AR) -x $(VCCRYPT_CORTEXMSOFT_RELEASE_LIB))
	mkdir -p $(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vccrypt
	(cd $(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vccrypt \
	    && $(CORTEXMHARD_RELEASE_AR) -x $(VCCRYPT_CORTEXMHARD_RELEASE_LIB))

extract.lib.vccert: libdepends
extract.lib.vccert:
	mkdir -p $(dir $(HOST_CHECKED_LIB))/libdepends/vccert
	(cd $(dir $(HOST_CHECKED_LIB))/libdepends/vccert \
	    && $(HOST_CHECKED_AR) -x $(VCCERT_HOST_CHECKED_LIB))
	mkdir -p $(dir $(HOST_RELEASE_LIB))/libdepends/vccert
	(cd $(dir $(HOST_RELEASE_LIB))/libdepends/vccert \
	    && $(HOST_RELEASE_AR) -x $(VCCERT_HOST_RELEASE_LIB))
	mkdir -p $(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vccert
	(cd $(dir $(CORTEXMSOFT_RELEASE_LIB))/libdepends/vccert \
	    && $(CORTEXMSOFT_RELEASE_AR) -x $(VCCERT_CORTEXMSOFT_RELEASE_LIB))
	mkdir -p $(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vccert
	(cd $(dir $(CORTEXMHARD_RELEASE_LIB))/libdepends/vccert \
	    && $(CORTEXMHARD_RELEASE_AR) -x $(VCCERT_CORTEXMHARD_RELEASE_LIB))

extract.lib.vcdb: libdepends
extract.lib.vcdb:
	mkdir -p $(dir $(HOST_CHECKED_LIB))/libdepends/vcdb
	(cd $(dir $(HOST_CHECKED_LIB))/libdepends/vcdb \
	    && $(HOST_CHECKED_AR) -x $(VCDB_HOST_CHECKED_LIB))
	mkdir -p $(dir $(HOST_RELEASE_LIB))/libdepends/vcdb
	(cd $(dir $(HOST_RELEASE_LIB))/libdepends/vcdb \
	    && $(HOST_RELEASE_AR) -x $(VCDB_HOST_RELEASE_LIB))

extract.lib.lmdb: libdepends
extract.lib.lmdb:
	mkdir -p $(dir $(HOST_CHECKED_LIB))/libdepends/lmdb
	(cd $(dir $(HOST_CHECKED_LIB))/libdepends/lmdb \
	    && $(HOST_CHECKED_AR) -x $(LMDB_HOST_RELEASE_LIB))
	mkdir -p $(dir $(HOST_RELEASE_LIB))/libdepends/lmdb
	(cd $(dir $(HOST_RELEASE_LIB))/libdepends/lmdb \
	    && $(HOST_RELEASE_AR) -x $(LMDB_HOST_RELEASE_LIB))

extract.lib.libevent: libdepends
extract.lib.libevent:
	mkdir -p $(dir $(HOST_CHECKED_LIB))/libdepends/libevent
	(cd $(dir $(HOST_CHECKED_LIB))/libdepends/libevent \
	    && $(HOST_CHECKED_AR) -x $(LIBEVENT_HOST_RELEASE_LIB))
	mkdir -p $(dir $(HOST_RELEASE_LIB))/libdepends/libevent
	(cd $(dir $(HOST_RELEASE_LIB))/libdepends/libevent \
	    && $(HOST_RELEASE_AR) -x $(LIBEVENT_HOST_RELEASE_LIB))

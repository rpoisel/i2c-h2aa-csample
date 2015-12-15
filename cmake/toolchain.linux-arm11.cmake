include(${CMAKE_CURRENT_LIST_DIR}/toolchain.env.cmake)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    set(RASPBERRY_DIR_BASE /usr/local/toolchains/arm-bcm2708/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64)
    set(RASPBERRY_DIR_COMPILER ${RASPBERRY_DIR_BASE}/bin)

    set(CMAKE_C_COMPILER ${RASPBERRY_DIR_COMPILER}/arm-linux-gnueabihf-gcc)
    set(RTS_PACKAGE_EXTRA_LINUX DEB)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    STRING(REPLACE "\\" "/" COMPILER_HOME $ENV{COMPILER_HOME})
    set(RASPBERRY_DIR_COMPILER ${COMPILER_HOME}/SysGCC/bin)

    set(CMAKE_C_COMPILER ${RASPBERRY_DIR_COMPILER}/arm-linux-gnueabihf-gcc.exe)
else()
    message(FATAL_ERROR Unsupported build platform.)
endif()

set(CMAKE_C_FLAGS "-std=c99 -Wall -Wextra -pedantic" CACHE STRING "C compiler flags")

# Name of the target platform
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Version of the system
set(CMAKE_SYSTEM_VERSION 1)

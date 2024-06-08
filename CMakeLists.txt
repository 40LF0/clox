cmake_minimum_required(VERSION 3.28)
project(clox)

set(CMAKE_C_STANDARD 23)

add_library(libclox SHARED
        lib/common.h
        lib/chuck.h
        lib/chuck.c
        lib/memory.h
        lib/memory.c
        lib/debug.h
        lib/debug.c
)

include_directories(lib)
add_executable(clox main.c
)
target_link_libraries(clox libclox)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
add_executable(google_test_run test/memory_test.cc)
target_link_libraries(google_test_run gtest gtest_main)
target_link_libraries(google_test_run libclox)
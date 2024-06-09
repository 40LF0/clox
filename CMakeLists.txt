cmake_minimum_required(VERSION 3.28)
project(clox)

set(CMAKE_C_STANDARD 23)

add_library(libclox SHARED
        lib/common.h
        lib/chunk.h
        lib/chunk.c
        lib/memory.h
        lib/memory.c
        lib/debug.h
        lib/debug.c
        lib/value.h
        lib/value.c
        lib/vm.h
        lib/vm.c
)

include_directories(lib)
add_executable(clox main.c)
target_link_libraries(clox libclox)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'google_test_run' is the target name
add_executable(google_test_run
        test/main_test.cc
        test/memory_test.cc
        test/debug_test.cc
        test/chunk_test.cc
        test/value_test.cc
)

target_link_libraries(google_test_run gtest gtest_main)
target_link_libraries(google_test_run libclox)
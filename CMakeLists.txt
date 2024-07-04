cmake_minimum_required(VERSION 3.28)
project(clox C)

# Set C standard to C17
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/Unity/src)

# Add source files
set(SOURCES
        lib/chunk.c
        lib/memory.c
        lib/debug.c
        lib/value.c
        lib/vm.c
        lib/compiler.c
        lib/scanner.c
        lib/object.c
        lib/table.c
)

# Add libclox library
add_library(libclox STATIC ${SOURCES})

# Add clox executable
add_executable(clox main.c)
target_link_libraries(clox libclox)

# Add Unity test framework
add_subdirectory(Unity)

# Function to add a test executable
function(add_test_executable test_name test_file)
    add_executable(${test_name} ${test_file})
    target_link_libraries(${test_name} libclox ${PROJECT_SOURCE_DIR}/Unity/src/unity.c)
    add_dependencies(${test_name} libclox)
endfunction()

# Add test executables
add_test_executable(chunk_test test/chunk_test.c)
add_test_executable(debug_test test/debug_test.c)
add_test_executable(memory_test test/memory_test.c)
add_test_executable(value_test test/value_test.c)
add_test_executable(scanner_test test/scanner_test.c)
cmake_minimum_required(VERSION 3.14)
project(DataStructures)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Shared library: data_structures
add_library(data_structures SHARED
    dynamic_array.cpp
    dynamic_array.h
)

# Executable: cli
add_executable(cli
    main.cpp
)
target_link_libraries(cli PRIVATE data_structures)

# GoogleTest integration
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Unit test executable (all files in root)
add_executable(unit_tests
    test_dynamic_array.cpp
)
target_link_libraries(unit_tests
    GTest::gtest_main
    data_structures
)

include(GoogleTest)
gtest_discover_tests(unit_tests)


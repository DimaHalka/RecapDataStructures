cmake_minimum_required(VERSION 3.14)

set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS 1 CACHE INTERNAL "No dev warnings")

project(RecapDataStructures)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library data_structures
add_library(data_structures INTERFACE
    dynamic_array.hpp
)

# Executable: cli
add_executable(cli
    main.cpp
)
target_link_libraries(cli PRIVATE data_structures)

# GoogleTest integration

set(BUILD_GMOCK OFF CACHE BOOL "Disable GoogleMock")
set(INSTALL_GMOCK OFF CACHE BOOL "Disable installing GoogleMock")

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Unit test executable
add_executable(unit_tests
    test_dynamic_array.cpp
)
target_link_libraries(unit_tests
    GTest::gtest_main
    data_structures
)

include(GoogleTest)

add_test(NAME DynamicArrayTest COMMAND unit_tests)

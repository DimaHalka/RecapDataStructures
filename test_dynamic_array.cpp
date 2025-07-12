#include <gtest/gtest.h>

#include "dynamic_array.hpp"

TEST(dynamic_array_test, ctor_default) {
    dynamic_array<int> a;
    EXPECT_EQ(a.size(), 0);
    EXPECT_EQ(a.capacity(), 2);
}

TEST(dynamic_array_test, push_back_increases_size) {
    dynamic_array<int> a;
    a.push_back(42);
    EXPECT_EQ(a.size(), 1);
    EXPECT_EQ(a.capacity(), 2);
    a.push_back(13);
    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(a.capacity(), 2);
}

TEST(dynamic_array_test, push_back_realloc) {
    dynamic_array<int> a;
    a.push_back(42);
    a.push_back(13);
    a.push_back(7);
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.capacity(), 4);
}

TEST(dynamic_array_test, push_back_at) {
    dynamic_array<int> a;
    a.push_back(42);
    EXPECT_EQ(a.at(0), 42);
    EXPECT_THROW(a.at(1), std::out_of_range);
}


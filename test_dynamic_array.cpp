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

TEST(dynamic_array_test, non_const_operator) {
    dynamic_array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    // Modify via non-const operator[]
    arr[1] = 99;
    EXPECT_EQ(arr[1], 99);
}

TEST(dynamic_array_test, const_operator) {
    dynamic_array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    const dynamic_array<int>& const_ref = arr;

    EXPECT_EQ(const_ref[0], 1);
    EXPECT_EQ(const_ref[1], 2);
    EXPECT_EQ(const_ref[2], 3);
}

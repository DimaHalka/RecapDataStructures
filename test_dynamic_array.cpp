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

TEST(dynamic_array_test, ctor_copy) {
    dynamic_array<int> original;
    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dynamic_array<int> copy = original;

    // Verify size and capacity
    EXPECT_EQ(copy.size(), original.size());
    EXPECT_EQ(copy.capacity(), original.capacity());

    // Verify elements
    for (std::size_t i = 0; i < copy.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }

    // Modify original and check copy is unaffected (deep copy)
    original[1] = 99;
    EXPECT_EQ(copy[1], 20);  // Copy should remain unchanged
}


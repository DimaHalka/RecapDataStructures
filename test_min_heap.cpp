#include <gtest/gtest.h>

#include "min_heap.hpp"

TEST(min_heap_test, empty) {
    min_heap<int> hp;
    ASSERT_EQ(hp.empty(), true);
    ASSERT_EQ(hp.size(), 0);
    EXPECT_THROW(hp.peek_min(), std::runtime_error);
    EXPECT_THROW(hp.extract_min(), std::runtime_error);
}

TEST(min_heap_test, extraction) {
    min_heap<int> hp;
    hp.insert(8);
    hp.insert(0);
    hp.insert(12);
    hp.insert(4);
    
    ASSERT_EQ(to_string(hp), "[ 0, 4, 12, 8 ]");
    ASSERT_EQ(hp.peek_min(), 0);
    ASSERT_EQ(hp.extract_min(), 0);
    ASSERT_EQ(hp.extract_min(), 4);
    ASSERT_EQ(hp.extract_min(), 8);
    ASSERT_EQ(hp.extract_min(), 12);
    ASSERT_EQ(hp.empty(), true);
}

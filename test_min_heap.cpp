#include <gtest/gtest.h>

#include "min_heap.hpp"

TEST(min_heap_test, simple) {
    min_heap<int> hp;
    hp.insert(8);
    hp.insert(0);
    hp.insert(12);
    hp.insert(4);
    
    ASSERT_EQ(hp.extract_min(), 0);
    ASSERT_EQ(hp.extract_min(), 4);
    ASSERT_EQ(hp.extract_min(), 8);
    ASSERT_EQ(hp.extract_min(), 12);    
}

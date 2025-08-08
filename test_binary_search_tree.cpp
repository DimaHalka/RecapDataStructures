#include <gtest/gtest.h>

#include "binary_search_tree.hpp"

TEST(binary_search_tree_test, ctor_default) {
    binary_search_tree<int> t;
    EXPECT_EQ(t.size(), 0);
}

TEST(binary_search_tree_test, add) {
    binary_search_tree<int> t;
    t.add(10);
    t.add(20);
    t.add(30);
    EXPECT_EQ(t.size(), 3);
    t.add(30);
    EXPECT_EQ(t.size(), 3);
}

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
    t.add(5);
    EXPECT_EQ(t.size(), 3);
    t.add(5);
    EXPECT_EQ(t.size(), 3);
}

TEST(binary_search_tree_test, is_there) {
    binary_search_tree<int> t;
    t.add(10);
    t.add(20);
    t.add(5);
    EXPECT_TRUE(t.contains(10));
    EXPECT_TRUE(t.contains(20));
    EXPECT_TRUE(t.contains(5));
    EXPECT_FALSE(t.contains(30));
}

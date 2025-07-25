#include <gtest/gtest.h>

#include "pair.hpp"

TEST(pair_test, empty) {
    pair<int, int> p;
}

TEST(pair_test, nonempty) {
    pair<int, int> p(42, 24);
    EXPECT_EQ(p.first(), 42);
    EXPECT_EQ(p.second(), 24);
}

TEST(pair_test, make) {
    auto p1 = make_pair(12, 88);
    EXPECT_EQ(p1.first(), 12);
    EXPECT_EQ(p1.second(), 88);
    
    auto p2 = make_pair<std::string, int>("Age", 50);
    EXPECT_EQ(p2.first(), "Age");
    EXPECT_EQ(p2.second(), 50);
}

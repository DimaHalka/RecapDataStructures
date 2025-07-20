#include <gtest/gtest.h>

#include "stack.hpp"

TEST(stack_test, empty) {
    stack<int> ss;
    EXPECT_EQ(ss.size(), 0);
    EXPECT_TRUE(ss.empty());
}

TEST(stack_test, push) {
    stack<int> ss;
    ss.push(42);
    EXPECT_EQ(ss.size(), 1);
    EXPECT_FALSE(ss.empty());
    ss.push(99);
    EXPECT_EQ(ss.size(), 2);
    ss.push(14);
    EXPECT_EQ(ss.size(), 3);
}

TEST(stack_test, pop) {
    stack<int> ss;
    ss.push(42);
    ss.push(99);
    ss.push(14);
    
    auto value = ss.pop();
    EXPECT_EQ(value, 14);
    EXPECT_EQ(ss.size(), 2);
    
    value = ss.pop();
    EXPECT_EQ(value, 99);
    EXPECT_EQ(ss.size(), 1);
    
    value = ss.pop();
    EXPECT_EQ(value, 42);
    EXPECT_EQ(ss.size(), 0);
    EXPECT_TRUE(ss.empty());
    
    EXPECT_THROW(ss.pop(), std::runtime_error);
}

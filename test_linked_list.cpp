#include <gtest/gtest.h>

#include "linked_list.hpp"

#include <sstream>

TEST(linked_list, empty) {
    linked_list<int> ll;
    EXPECT_EQ(ll.size(), 0);
    EXPECT_TRUE(ll.empty());
    EXPECT_THROW(ll.front(), std::runtime_error);
    EXPECT_THROW(ll.back(), std::runtime_error);
    EXPECT_THROW(ll.pop_front(), std::runtime_error);
}

TEST(linked_list, copy_ctor) {
    linked_list<int> ll;
    ll.push_back(42);
    ll.push_back(99);
    ll.push_back(14);
    
    linked_list<int> copy(ll);
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.front(), 42);
    EXPECT_EQ(copy.back(), 14);
}

TEST(linked_list, size) {
    linked_list<int> ll;
    ll.push_back(42);
    ll.push_back(99);
    ll.push_back(14);
    EXPECT_EQ(ll.size(), 3);
}

TEST(linked_list, push_back) {
    linked_list<int> ll;
    ll.push_back(42);
    EXPECT_EQ(ll.front(), 42);
    EXPECT_EQ(ll.back(), 42);
    ll.push_back(99);
    EXPECT_EQ(ll.front(), 42);
    EXPECT_EQ(ll.back(), 99);
    ll.push_back(14);
    EXPECT_EQ(ll.front(), 42);
    EXPECT_EQ(ll.back(), 14);
}

TEST(linked_list, push_front) {
    linked_list<int> ll;
    ll.push_front(42);
    EXPECT_EQ(ll.front(), 42);
    EXPECT_EQ(ll.back(), 42);
    ll.push_front(99);
    EXPECT_EQ(ll.front(), 99);
    EXPECT_EQ(ll.back(), 42);
    ll.push_front(14);
    EXPECT_EQ(ll.front(), 14);
    EXPECT_EQ(ll.back(), 42);
}


TEST(linked_list, pop_front) {
    linked_list<int> ll;
    ll.push_back(42);
    ll.push_back(99);
    ll.push_back(14);
    EXPECT_EQ(ll.front(), 42);
    ll.pop_front();
    EXPECT_EQ(ll.front(), 99);
    ll.pop_front();
    EXPECT_EQ(ll.front(), 14);
    ll.pop_front();
    EXPECT_THROW(ll.pop_front(), std::runtime_error);    
}

TEST(linked_list, pop_back) {
    linked_list<int> ll;
    ll.push_back(42);
    ll.push_back(99);
    ll.push_back(14);
    EXPECT_EQ(ll.back(), 14);
    ll.pop_back();
    EXPECT_EQ(ll.back(), 99);
    ll.pop_back();
    EXPECT_EQ(ll.back(), 42);
    ll.pop_back();
    EXPECT_THROW(ll.pop_back(), std::runtime_error);
}

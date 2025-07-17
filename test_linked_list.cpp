#include <gtest/gtest.h>

#include "linked_list.hpp"

#include <sstream>

TEST(linked_list, push_back) {
    linked_list<int> ll;
    ll.push_back(42);
    ll.push_back(99);
    EXPECT_EQ(ll.size(), 2);
    
    linked_list<int>::iterator it = ll.begin();
    EXPECT_EQ(*it, 42);
    ++it;
    EXPECT_EQ(*it, 99);
    
    std::stringstream ss;
    ss << ll;
    EXPECT_EQ(ss.str(), "[ 42, 99 ]");
}

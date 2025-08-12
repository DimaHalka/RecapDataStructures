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

TEST(binary_search_tree_test, contains) {
    binary_search_tree<int> t;
    t.add(10);
    t.add(20);
    t.add(5);
    EXPECT_TRUE(t.contains(10));
    EXPECT_TRUE(t.contains(20));
    EXPECT_TRUE(t.contains(5));
    EXPECT_FALSE(t.contains(30));
}

TEST(binary_search_tree_test, copy_ctor) {
    binary_search_tree<int> t;
    t.add(100);
    t.add(200);
    t.add(50);
    t.add(25);
    t.add(75);
    
    binary_search_tree<int> copy(t);
    EXPECT_EQ(copy.size(), 5);
    EXPECT_TRUE(copy.contains(100));
    EXPECT_TRUE(copy.contains(200));
    EXPECT_TRUE(copy.contains(50));
    EXPECT_TRUE(copy.contains(25));
    EXPECT_TRUE(copy.contains(75));
}

TEST(binary_search_tree_test, assign_op) {
    binary_search_tree<int> t0;
    t0.add(100);
    t0.add(200);
    t0.add(50);
    t0.add(25);
    t0.add(75);
    
    binary_search_tree<int> copy = t0;
    EXPECT_EQ(copy.size(), 5);
    EXPECT_TRUE(copy.contains(100));
    EXPECT_TRUE(copy.contains(200));
    EXPECT_TRUE(copy.contains(50));
    EXPECT_TRUE(copy.contains(25));
    EXPECT_TRUE(copy.contains(75));
}

TEST(binary_search_tree_test, compare_op) {
    binary_search_tree<int> t0;

    binary_search_tree<int> t1;
    t1.add(100);
    t1.add(200);
    t1.add(50);
    t1.add(25);
    t1.add(75);

    binary_search_tree<int> t2;
    t2.add(100);

    binary_search_tree<int> t3;
    t2.add(0);

    binary_search_tree<int> copy = t1;
    
    bool b1 = (t1 == copy);
    
    EXPECT_TRUE(t1 == copy);
    EXPECT_FALSE(t1 == t0);
    EXPECT_FALSE(t1 == t2);
    EXPECT_FALSE(t1 == t3);    
}

TEST(binary_search_tree_test, traverse_bfs) {
    binary_search_tree<int> t;
    t.add(100);
    t.add(200);
    t.add(50);
    t.add(25);
    t.add(75);
    
    std::string str;
    t.traverse_bfs([&](const int& value){
        str += std::to_string(value) + " ";
    });
    std::string trimmed(str.c_str(), str.length()-1);
    EXPECT_EQ(trimmed, "100 200 50 75 25");
}

TEST(binary_search_tree_test, traverse_inorder) {
    binary_search_tree<int> t;
    t.add(100);
    t.add(200);
    t.add(50);
    t.add(25);
    t.add(75);
    
    std::string str;
    t.traverse_inorder([&](const int& value){
        str += std::to_string(value) + " ";
    });
    std::string trimmed(str.c_str(), str.length()-1);
    EXPECT_EQ(trimmed, "25 50 75 100 200");
}


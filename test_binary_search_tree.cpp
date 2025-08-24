#include <gtest/gtest.h>

#include "binary_search_tree.hpp"

namespace {
template <typename T>
std::string inorder_str(const binary_search_tree<T>& t) {
    std::string s;
    t.traverse_inorder([&](const T& v){ s += std::to_string(v) + " "; });
    if (!s.empty()) s.pop_back();
    return s;
}
}


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
    
    binary_search_tree<int> copy;
    copy = t0;
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
    
    EXPECT_EQ(inorder_str(t), "25 50 75 100 200");
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


TEST(binary_search_tree_remove, remove_from_empty) {
    binary_search_tree<int> t;
    EXPECT_FALSE(t.remove(10));
    EXPECT_EQ(t.size(), 0u);
    EXPECT_EQ(inorder_str(t), "");
}

TEST(binary_search_tree_remove, remove_nonexistent) {
    binary_search_tree<int> t;
    t.add(10); t.add(5); t.add(20);
    EXPECT_FALSE(t.remove(999));
    EXPECT_EQ(t.size(), 3u);
    EXPECT_TRUE(t.contains(10));
    EXPECT_TRUE(t.contains(5));
    EXPECT_TRUE(t.contains(20));
    EXPECT_EQ(inorder_str(t), "5 10 20");
}

TEST(binary_search_tree_remove, remove_leaf) {
    binary_search_tree<int> t;
    t.add(100); t.add(200); t.add(50); t.add(25); t.add(75);
    EXPECT_TRUE(t.remove(25));
    EXPECT_EQ(t.size(), 4u);
    EXPECT_FALSE(t.contains(25));
    EXPECT_EQ(inorder_str(t), "50 75 100 200");
}

TEST(binary_search_tree_remove, remove_node_with_only_right_child) {
    //       10
    //      /  \
    //     5   20
    //           \
    //            25
    binary_search_tree<int> t;
    t.add(10); t.add(5); t.add(20); t.add(25);
    EXPECT_TRUE(t.remove(20));
    EXPECT_EQ(t.size(), 3u);
    EXPECT_TRUE(t.contains(25));
    EXPECT_EQ(inorder_str(t), "5 10 25");
}

TEST(binary_search_tree_remove, remove_node_with_only_left_child) {
    //       10
    //      /  \
    //     5   20
    //    /
    //   3
    binary_search_tree<int> t;
    t.add(10); t.add(5); t.add(20); t.add(3);
    EXPECT_TRUE(t.remove(5));
    EXPECT_EQ(t.size(), 3u);
    EXPECT_TRUE(t.contains(3));
    EXPECT_EQ(inorder_str(t), "3 10 20");
}

TEST(binary_search_tree_remove, remove_root_when_single_node) {
    binary_search_tree<int> t;
    t.add(42);
    EXPECT_TRUE(t.remove(42));
    EXPECT_EQ(t.size(), 0u);
    EXPECT_FALSE(t.contains(42));
    EXPECT_EQ(inorder_str(t), "");
}

TEST(binary_search_tree_remove, remove_root_with_only_right_child) {
    // 10
    //   \
    //    20
    binary_search_tree<int> t;
    t.add(10); t.add(20);
    EXPECT_TRUE(t.remove(10)); // корінь має лише правого
    EXPECT_EQ(t.size(), 1u);
    EXPECT_TRUE(t.contains(20));
    EXPECT_EQ(inorder_str(t), "20");
}

TEST(binary_search_tree_remove, remove_root_with_only_left_child) {
    //   10
    //  /
    // 5
    binary_search_tree<int> t;
    t.add(10); t.add(5);
    EXPECT_TRUE(t.remove(10)); // корінь має лише лівого
    EXPECT_EQ(t.size(), 1u);
    EXPECT_TRUE(t.contains(5));
    EXPECT_EQ(inorder_str(t), "5");
}

TEST(binary_search_tree_remove, remove_node_with_two_children_successor_is_right_child) {
    //    10
    //   /  \
    //  5   15
    binary_search_tree<int> t;
    t.add(10); t.add(5); t.add(15);
    EXPECT_TRUE(t.remove(10));
    EXPECT_EQ(t.size(), 2u);
    EXPECT_TRUE(t.contains(15));
    EXPECT_EQ(inorder_str(t), "5 15");
}

TEST(binary_search_tree_remove, remove_node_with_two_children_successor_deep_with_right_child) {
    //        10
    //       /  \
    //      5    20
    //          /
    //        15
    //          \
    //           16
    //
    binary_search_tree<int> t;
    t.add(10); t.add(5); t.add(20); t.add(15); t.add(16);
    EXPECT_TRUE(t.remove(10));
    EXPECT_EQ(t.size(), 4u);
    
    EXPECT_TRUE(t.contains(15));
    EXPECT_TRUE(t.contains(16));
    EXPECT_TRUE(t.contains(20));
    EXPECT_TRUE(t.contains(5));
    EXPECT_EQ(inorder_str(t), "5 15 16 20");
}

TEST(binary_search_tree_remove, remove_twice_idempotent) {
    binary_search_tree<int> t;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) t.add(v);
    EXPECT_TRUE(t.remove(30));
    EXPECT_FALSE(t.remove(30));
    EXPECT_EQ(t.size(), 6u);
    EXPECT_FALSE(t.contains(30));
    EXPECT_EQ(inorder_str(t), "20 40 50 60 70 80");
}

TEST(binary_search_tree_remove, remove_all_one_by_one) {
    binary_search_tree<int> t;
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int v : vals) t.add(v);
    EXPECT_EQ(t.size(), 7u);

    EXPECT_TRUE(t.remove(20));
    EXPECT_TRUE(t.remove(30));
    EXPECT_TRUE(t.remove(70));
    EXPECT_TRUE(t.remove(50));
    EXPECT_TRUE(t.remove(40));
    EXPECT_TRUE(t.remove(60));
    EXPECT_TRUE(t.remove(80));

    EXPECT_EQ(t.size(), 0u);
    EXPECT_EQ(inorder_str(t), "");
}

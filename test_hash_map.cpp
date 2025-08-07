#include <gtest/gtest.h>

#include "hash_map.hpp"

TEST(hash_map_test, empty) {
    hash_map<std::string, int> hm;
}

TEST(hash_map_test, insert) {
    hash_map<std::string, int> hm;
    hm.insert("Dmytro Halka", 5433549);
    EXPECT_EQ(hm.size(), 1);
    EXPECT_EQ(hm.get("Dmytro Halka"), 5433549);
    EXPECT_THROW(hm.get("John Dow"), std::runtime_error);
}

TEST(hash_map_test, update) {
    hash_map<std::string, int> hm;
    hm.insert("Dmytro Halka", 5433549);
    hm.insert("Dmytro Halka", 5433550);
    EXPECT_EQ(hm.size(), 1);
    EXPECT_EQ(hm.get("Dmytro Halka"), 5433550);
}

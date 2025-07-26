#include <gtest/gtest.h>

#include "hash_map.hpp"

TEST(hash_map_test, empty) {
    hash_map<std::string, int> hm;
}

TEST(hash_map_test, insert_get) {
    hash_map<std::string, int> hm;
    // hm.insert("Dmytro Halka", 5433549);
    // EXPECT_EQ(hm.get("Dmytro Halka"), 5433549);
}

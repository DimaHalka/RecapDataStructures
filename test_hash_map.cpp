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

TEST(hash_map_test, insert_bulk) {
    auto _key = [](int idx){
        return "key-" + std::to_string(idx);
    };
    
    hash_map<std::string, int> hm;
    for(auto i = 0U; i<1024; i++)
        hm.insert(_key(i), i);
    
    EXPECT_EQ(hm.size(), 1024);
    for(auto i = 0U; i<1024; i++)
        EXPECT_EQ(hm.get(_key(i)), i);
}

#pragma once

#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "pair.hpp"

template<typename Key, typename Value>
class hash_map {
public:
    hash_map()
        : m_size(8)
        , m_load_factor(0.75) {
        // TODO: resize m_data
    }
    
    void insert(const Key& key, const Value& value) {
        // std::size_t idx = hash(key);
        // bucket& buck = m_data[idx];
        // buck.push_back(make_pair(key, value));
    }
    
    const Value& get(const Key& key) const {
        // std::size_t idx = hash(key);
        // const bucket& buck = m_data[idx];
        // for(auto it=buck.begin(); it!=buck.end(); ++it) {
        // }
    }
    
private:
    using bucket = linked_list<pair<Key, Value>>;

private:
     std::size_t hash(Key key) const {
        return std::hash<Key>{}(key);
    }
    
private:
    std::size_t m_size;
    float m_load_factor;
    dynamic_array<bucket> m_data;
};

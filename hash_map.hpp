#pragma once

#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "pair.hpp"

template<typename Key, typename Value>
class hash_map {
public:
    hash_map()
        : m_buckets(8)
        , m_size(0)
        , m_load_factor(0.75) {
        m_data.resize(m_buckets);
    }
    
    std::size_t size() const noexcept {
        return m_size;
    }
    
    void insert(const Key& key, const Value& value) {
        std::size_t idx = hash(key) % m_buckets;
        bucket& buck = m_data[idx];
        for(auto it=buck.begin(); it!=buck.end(); ++it){
            if((*it).first() == key) {
                (*it).second() = value; // update existing
                return;
            }
        }
        buck.push_back(make_pair(key, value)); // insert new
        m_size++;
    }
    
    const Value& get(const Key& key) const {
        std::size_t idx = hash(key) % m_buckets;
        const bucket& buck = m_data[idx];
        for(auto it=buck.begin(); it!=buck.end(); ++it) {
            if((*it).first() == key)
                return (*it).second();
        }
        throw std::runtime_error("hash_map::get - no such item");
    }
    
private:
    using bucket = linked_list<pair<Key, Value>>;

private:
     std::size_t hash(Key key) const {
        return std::hash<Key>{}(key);
    }
    
private:
    std::size_t m_size;
    std::size_t m_buckets;
    float m_load_factor;
    dynamic_array<bucket> m_data;
};

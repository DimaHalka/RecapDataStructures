#pragma once

#include "dynamic_array.hpp"
#include "linked_list.hpp"
#include "pair.hpp"

template<typename Key, typename Value>
class hash_map {
public:
    hash_map()
        : m_size(0)
        , m_load_factor(0.75) {
        m_buckets.resize(8);
    }
    
    std::size_t size() const noexcept {
        return m_size;
    }
    
    void insert(const Key& key, const Value& value) {
        if(m_size + 1 > m_load_factor * m_buckets.size())
            _rehash();
            
        if(_insert(m_buckets, std::move(key), std::move(value)))
            m_size++;
    }
    
    const Value& get(const Key& key) const {
        std::size_t idx = _hash(key) % m_buckets.size();
        const bucket& buck = m_buckets[idx];
        for(auto it=buck.begin(); it!=buck.end(); ++it) {
            if((*it).first() == key)
                return (*it).second();
        }
        throw std::runtime_error("hash_map::get - no such item");
    }
    
private:
    using bucket = linked_list<pair<Key, Value>>;

     std::size_t _hash(Key key) const {
        return std::hash<Key>{}(key);
    }
    
    std::size_t _rehash() {
        dynamic_array<bucket> new_buckets;
        new_buckets.resize(m_buckets.size() * 2);
        for(std::size_t idx = 0U; idx < m_buckets.size(); idx++) {
            const auto& buck = m_buckets[idx];
            for(auto elem = buck.begin(); elem != buck.end(); ++elem) {
                _insert(new_buckets, (*elem).first(), (*elem).second());
            }
        }
        
        // m_size doesn't change
        std::swap(m_buckets, new_buckets);
    }
    
    // insert with no rehash
    bool _insert(dynamic_array<bucket>& buckets, const Key& key, const Value& value) {
        std::size_t idx = _hash(key) % buckets.size();
        bucket& buck = buckets[idx];
        for(auto it=buck.begin(); it!=buck.end(); ++it){
            if((*it).first() == key) {
                (*it).second() = value; // update existing
                return false;
            }
        }
        buck.push_back(make_pair(key, value)); // insert new
        return true;
    }

    
private:
    std::size_t m_size;
    float m_load_factor;
    dynamic_array<bucket> m_buckets;
};

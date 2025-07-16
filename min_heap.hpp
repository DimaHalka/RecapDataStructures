#pragma once

#include "dynamic_array.hpp"

/*
 visual:
             2
        /        \
       3          5
      /  \      /   \
    17    7    25    6
   /  \
  22   18
 
 in-memory:
   2  3  5  17  7  25  6  22  18
 
 indexes:
   idx_parent = (idx-1)/2
   idx_left   = (idx*2)+1
   idx_right  = (idx*2)+2
*/

template<typename T>
class min_heap {
public:
    T extract_min() {
        if(m_data.size() == 0)
            throw std::runtime_error("min_heap::extract_min - container empty");
        T value = std::move(m_data[0]);
        m_data[0] = std::move(m_data[m_data.size()-1]);
        m_data.pop_back();
        if (m_data.size() > 0) {
            heapify_down(0);
        }
        return value;
    }
    
    void insert(const T& obj){
        m_data.push_back(obj);
        heapify_up(m_data.size()-1);
    }
    
    std::size_t size() const {
        return m_data.size();
    }
    
private:
    void heapify_up(std::size_t idx){
        while(idx > 0) {
            if(m_data[idx] < m_data[parent(idx)]) {
                std::swap(m_data[idx], m_data[parent(idx)]);
                idx = parent(idx);
            }
            else {
                break;
            }
        }
    }
    
    void heapify_down(std::size_t idx){
        while(true) {
            // swap with the smallest child (not any of them)
            std::size_t idx_for_swap = idx;
            
            if(left(idx) >= m_data.size() && right(idx) >= m_data.size()){
                // no children at all
                break;
            }
            else if(left(idx) < m_data.size() && right(idx) < m_data.size()){
                // both children, who is smaller?
                idx_for_swap = m_data[right(idx)] < m_data[left(idx)] ?
                    right(idx) : left(idx);
            }
            else if(left(idx) < m_data.size() && right(idx) >= m_data.size()){
                // no right child
                idx_for_swap = left(idx);
            }
            else {
                // cannot have right and no left
                assert(false);
            }
            
            if(idx_for_swap != idx && m_data[idx] > m_data[idx_for_swap]) {
                std::swap(m_data[idx], m_data[idx_for_swap]);
                idx = idx_for_swap; // continue
            }
            else {
                // no need to swap
                break;
            }
        }
    }
    
    std::size_t parent(std::size_t idx) const {
        return (idx-1)/2;
    }

    std::size_t left(std::size_t idx) const {
        return (idx*2)+1;
    }
    
    std::size_t right(std::size_t idx) const {
        return (idx*2)+2;
    }

private:
    dynamic_array<T> m_data;
    
template <typename U>
friend std::string to_string(const min_heap<U>&);
};


template <typename T>
std::string to_string(const min_heap<T>& hp) {
    std::ostringstream oss;
    oss << hp.m_data;
    return oss.str();
}

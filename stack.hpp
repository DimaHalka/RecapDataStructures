#pragma once

#include "linked_list.hpp"

template<typename T>
class stack {
public:
    void push(const T& object) {
        m_data.push_front(object);
    }
    
    T pop() {
        if(empty()) {
            throw std::runtime_error("stack::pop - stack empty");
        }
        
        auto object = m_data.front();
        m_data.pop_front();
        return object;
    }
    
    std::size_t size() const noexcept {
        return m_data.size();
    }
    
    std::size_t empty() const noexcept {
        return m_data.empty();
    }

private:
    linked_list<T> m_data;
};

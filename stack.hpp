#pragma once

#include "linked_list.hpp"

template<typename T>
class stack {
public:
    void push(const T& object) {
        m_data.push_front(object);
    }
    
    void push(T&& object) {
        m_data.push_front(std::move(object));
    }

    T pop() {
        if(empty()) {
            throw std::runtime_error("stack::pop - stack empty");
        }
        
        return m_data.pop_front();
    }
    
    const T& top() const {
        if(empty()) {
            throw std::runtime_error("stack::top - stack empty");
        }
        
        return m_data.front();
    }

    std::size_t size() const noexcept {
        return m_data.size();
    }
    
    bool empty() const noexcept {
        return m_data.empty();
    }

private:
    linked_list<T> m_data;
};

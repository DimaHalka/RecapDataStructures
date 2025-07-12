#pragma once

#include <cstddef> // std::size_t

template<typename T>
class dynamic_array {
public:
    dynamic_array()
        : m_size(0)
        , m_capacity(2)
        , mp_data(new T[2])
    {
    }
    
    ~dynamic_array() noexcept {
        delete[] mp_data;
    }

    std::size_t size() const noexcept {
        return m_size;
    }
    
    std::size_t capacity() const noexcept {
        return m_capacity;
    }
    
    void push_back(const T& obj) {
        if (m_size == m_capacity)
            reallocate();
        mp_data[m_size++] = obj;
    }
    
    const T& at(std::size_t idx) const {
        // Like standard containers, check for out of bounds
        if (idx >= m_size)
            throw std::out_of_range("dynamic_array::at - index out of range");
        return mp_data[idx];
    }
    
    const T& operator[](std::size_t idx) const noexcept {
        // Like standard containers, no bounds check
        return mp_data[idx];
    }

    T& operator[](std::size_t idx) noexcept {
        // Like standard containers, no bounds check
        return mp_data[idx];
    }

private:
    void reallocate() {
        // exception safety: new T[m_capacity] or T::operator= may throw
        // so allocate the new data, once succeeded - swap
        std::size_t new_capacity = m_capacity * 2;
        T* p_new_data = new T[new_capacity];

        for (std::size_t i = 0; i < m_size; ++i) {
            p_new_data[i] = std::move(mp_data[i]);
        }

        // allocation was OK, we can safely swap now
        std::swap(mp_data, p_new_data);
        m_capacity = new_capacity;

        delete[] p_new_data;
    }
    
private:
    T* mp_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

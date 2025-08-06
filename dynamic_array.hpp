#pragma once

#include <cstddef> // std::size_t
#include <sstream>

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
    
    dynamic_array(const dynamic_array& other)
        : m_size(other.m_size)
        , m_capacity(other.m_capacity)
        , mp_data(new T[other.m_capacity])
    {
        std::copy(other.mp_data, other.mp_data + m_size, mp_data);
    }
    
    dynamic_array(dynamic_array&& other) noexcept
        : mp_data(other.mp_data)
        , m_size(other.m_size)
        , m_capacity(other.m_capacity)
    {
        other.mp_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    
    dynamic_array& operator=(const dynamic_array& other) {
        // exception safety: new T[m_capacity] or std::copy(...) may throw
        if (this != &other) {
            dynamic_array temp(other);  // may throw, but leaves *this untouched
            std::swap(mp_data, temp.mp_data);
            std::swap(m_size, temp.m_size);
            std::swap(m_capacity, temp.m_capacity);
        }
        return *this;
    }

    dynamic_array& operator=(dynamic_array&& other) noexcept {
        if (this != &other) {
            delete[] mp_data;  

            mp_data = other.mp_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.mp_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    std::size_t size() const noexcept {
        return m_size;
    }
    
    std::size_t capacity() const noexcept {
        return m_capacity;
    }
    
    void push_back(const T& object) {
        if (m_size == m_capacity)
            _reallocate(m_capacity*2);
        
        mp_data[m_size++] = object;
    }
    
    void pop_back() {
        if (m_size == 0)
            throw std::out_of_range("dynamic_array::pop - container empty");
                
        m_size--;
        
        // delete &mp_data[m_size]; is undefined behavior for array elements
        mp_data[m_size].~T();

        _shrink();
    }

    const T& at(std::size_t idx) const {
        // like standard containers, check for out of bounds
        if (idx >= m_size)
            throw std::out_of_range("dynamic_array::at - index out of range");
        return mp_data[idx];
    }
    
    const T& operator[](std::size_t idx) const noexcept {
        // like standard containers, no bounds check
        return mp_data[idx];
    }

    T& operator[](std::size_t idx) noexcept {
        // like standard containers, no bounds check
        return mp_data[idx];
    }

    void resize(std::size_t new_size) {
        if(new_size < m_size) {
            for(std::size_t i = new_size; i < m_size; ++i) {
                mp_data[i].~T();
            }
            _shrink();
        }
        else if(new_size > m_size) {
            if (new_size >= m_capacity)
                _reallocate(new_size*2);
            for(std::size_t i = m_size; i < new_size; ++i) {
                mp_data[i] = {};
            }
        }
        m_size = new_size;
    }
    
private:
    void _reallocate(std::size_t new_capacity) {
        // exception safety: new T[new_capacity] or T::operator= may throw
        // so allocate the new data, once succeeded - swap
        T* p_new_data = new T[new_capacity];

        for (std::size_t i = 0; i < m_size; ++i) {
            p_new_data[i] = std::move(mp_data[i]);
        }

        // allocation was OK, we can safely swap now
        T* p_old_data = mp_data;
        std::swap(mp_data, p_new_data);
        m_capacity = new_capacity;

        delete[] p_old_data;
    }
    
    void _shrink() {
        if (m_size < m_capacity / 4 && m_capacity > 2) {
            _reallocate(m_size > 1 ? m_size * 2 : 2);
        }
    }
    
private:
    T* mp_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const dynamic_array<T>& arr) {
    os << "[ ";
    for (std::size_t i = 0; i < arr.size(); ++i) {
        os << arr[i];
        if (i + 1 != arr.size()) os << ", ";
    }
    os << " ]";
    return os;
}

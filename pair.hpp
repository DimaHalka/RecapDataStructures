#pragma once

template<typename T1, typename T2>
struct pair {
    pair() = default;
    ~pair() = default;

    pair(const T1& obj1, const T2& obj2)
        : m_obj1(obj1)
        , m_obj2(obj2) {
        }

    pair(const pair& other) = default;
    
    pair(pair&& other) = default;
    
    pair& operator=(const pair& other) = default;
    
    pair& operator=(pair&& other) = default;
    
    bool operator==(const pair& other) const {
        return m_obj1 == other.m_obj1 && m_obj2 == other.m_obj2;
    }
    
    T1& first() {
        return m_obj1;
    }

    const T1& first() const {
        return m_obj1;
    }

    T2& second() {
        return m_obj2;
    }

    const T2& second() const {
        return m_obj2;
    }

private:
    T1 m_obj1;
    T2 m_obj2;
};

// TODO: should support perfect forwarding
template<typename T1, typename T2>
pair<T1, T2> make_pair(const T1& obj1, const T2& obj2) {
    return pair<T1, T2>(obj1, obj2);
}

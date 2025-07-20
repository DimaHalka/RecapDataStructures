#pragma once

template <typename T>
class linked_list {
    struct node;
    
public:
    linked_list()
    : mp_head(nullptr)
    , mp_tail(nullptr)
    , m_size(0) {
    }
    
    ~linked_list() {
        _free();
    }
    
    linked_list(const linked_list& other) {
        mp_head = mp_tail = nullptr;
        m_size = 0;
        if(!other.empty()) {
            auto* p = other.mp_head;
            while(p) {
                push_back(p->m_obj);
                p = p->mp_next;
            }
        }
    }
    
    linked_list(linked_list&& other)
    : mp_head(other.mp_head)
    , mp_tail(other.mp_tail)
    , m_size(other.m_size)
    {
        other.mp_head = other.mp_tail = nullptr;
        other.m_size = 0;
    }
    
    linked_list& operator=(const linked_list& other) {
        if(this != &other){
            linked_list tmp(other); // may throw, but leaves *this untouched
            std::swap(tmp.mp_head, mp_head);
            std::swap(tmp.mp_tail, mp_tail);
            std::swap(tmp.m_size, m_size);
        }
        return *this;
    }
    
    linked_list& operator=(linked_list&& other) {
        if(this != &other){
            _free();
            mp_head = other.mp_head;
            mp_tail = other.mp_tail;
            m_size = other.m_size;
            other.mp_head = other.mp_tail = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    
    const T& front() const {
        if(!mp_head) {
            throw std::runtime_error("linked_list::front - list empty");
        }
        
        return mp_head->m_obj;
    }
    
    const T& back() const {
        if(!mp_tail) {
            throw std::runtime_error("linked_list::back - list empty");
        }
        
        return mp_tail->m_obj;
    }
    
    void push_front(const T& obj){
        auto* p_new_node = new node(obj);
        if(!mp_head) {
            mp_head = mp_tail = p_new_node;
        }
        else {
            auto* p_old_head = mp_head;
            mp_head = p_new_node;
            mp_head->mp_next = p_old_head;
        }
        m_size++;
    }
    
    void push_back(const T& obj){
        auto* p_new_node = new node(obj);
        if(!mp_head) {
            mp_head = mp_tail = p_new_node;
        }
        else {
            mp_tail->mp_next = p_new_node;
            mp_tail = p_new_node;
        }
        m_size++;
    }
    
    void pop_front() {
        if(!mp_head) {
            throw std::runtime_error("linked_list::pop_front - list empty");
        }
        else if(mp_head && m_size == 1) {
            delete mp_head;
            mp_head = mp_tail = nullptr;
            m_size = 0;
        }
        else {
            auto* p_new_head = mp_head->mp_next;
            delete mp_head;
            mp_head = p_new_head;
            m_size--;
        }
    }
    
    void pop_back() {
        if(!mp_tail) {
            throw std::runtime_error("linked_list::pop_back - list empty");
        }
        else if(mp_tail && m_size == 1) {
            delete mp_tail;
            mp_head = mp_tail = nullptr;
            m_size = 0;
        }
        else {
            node* p_new_tail = mp_head;
            while(true) {
                if(p_new_tail->mp_next == mp_tail)
                    break;
                p_new_tail = p_new_tail->mp_next;
            }
            delete mp_tail;
            mp_tail = p_new_tail;
            m_size--;
        }
    }
    
    std::size_t size() const noexcept {
        return m_size;
    }
    
    bool empty() const noexcept {
        return m_size == 0;
    }
    
    void clear() {
        _free();
    }
    
    class iterator {
    public:
        explicit iterator(node* p_node)
        : mp_node(p_node) {
        }
        
        T& operator* () {
            return mp_node->m_obj;
        }
        
        iterator& operator++() {
            mp_node = mp_node->mp_next;
            return *this;
        }
        
        bool operator!=(const iterator& other) const {
            return mp_node != other.mp_node;
        }
        
    private:
        node* mp_node;
    }; // end of class iterator
    
    iterator begin(){
        return iterator(mp_head);
    }
    
    iterator end(){
        return iterator(nullptr);
    }
    
private:
    node* mp_head;
    node* mp_tail;
    std::size_t m_size;
    
    void _free() {
        auto* p = mp_head;
        while(p) {
            auto* p_next = p->mp_next;
            delete p;
            p = p_next;
        }
        mp_head = mp_tail = nullptr;
        m_size = 0;
    }
    
    struct node{
        node(const T& obj)
            : mp_next(nullptr)
            , m_obj(obj) {
        }
        
        node* mp_next;
        T m_obj;
    };
};

template <typename T>
std::ostream& operator<<(std::ostream& os, linked_list<T>& ll) {
    os << "[ ";
    
    bool first = true;
    for (auto it = ll.begin(); it != ll.end(); ++it) {
        if (!first) os << ", ";
        os << *it;
        first = false;
    }
    
    os << " ]";
    return os;
}

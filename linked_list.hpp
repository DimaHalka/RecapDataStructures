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
        auto* p = mp_head;
        while(p) {
            auto* p_next = p->mp_next;
            delete p;
            p = p_next;
        }
    }
    
    T front() const {
        if(!mp_head) {
            throw std::runtime_error("linked_list::front - list empty");
        }
        
        return mp_head->m_obj;
    }

    T back() const {
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
    
    int i = 0;
    for (auto it = ll.begin(); it != ll.end(); ++it) {
        os << *it;
        if (i + 1 != ll.size()) os << ", ";
        i++;
    }
    
    os << " ]";
    return os;
}

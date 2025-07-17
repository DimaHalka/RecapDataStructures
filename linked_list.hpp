#pragma once

template <typename T>
class linked_list {
    struct node{
        node(const T& obj)
            : mp_next(nullptr)
            , m_obj(obj) {
        }
        
        node* mp_next;
        T m_obj;
    };
    
public:
    linked_list()
        : mp_head(nullptr)
        , mp_tail(nullptr)
        , m_size(0) {
        
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
    
    std::size_t size() const noexcept {
        return m_size;
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
    };
    
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

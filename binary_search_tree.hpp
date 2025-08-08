#pragma once

#include "linked_list.hpp"

template <typename T>
class binary_search_tree {
public:
    binary_search_tree()
        : mp_root(nullptr)
        , m_size(0) {
    }
 
    ~binary_search_tree() noexcept {
        if(!mp_root)
            return;
        
        linked_list<node*> queue;
        queue.push_back(mp_root);
        while (!queue.empty()) {
            node* p = queue.pop_front();
            if(p->left)
                queue.push_back(p->left);
            if(p->right)
                queue.push_back(p->right);
            delete p;
        }
        
        mp_root = nullptr;
        m_size = 0;
    }
    
    binary_search_tree(const binary_search_tree&) {
        throw 0; // copy ctor
    }

    binary_search_tree& operator=(const binary_search_tree&) {
        throw 0; // assignment operator
    }

    binary_search_tree(binary_search_tree&&) {
        throw 0; // move ctor
    }

    binary_search_tree& operator=(binary_search_tree&&) {
        throw 0; // move op
    }
    
    size_t size() const noexcept {
        return m_size;
    }
    
    void add(const T& value) {
        if(!mp_root) {
            mp_root = new node(value);
            m_size++;
            return;
        }
        
        node* p_node = mp_root;
        while (p_node) {
            if(p_node->value == value) {
                return;
            }
            if(value > p_node->value && !p_node->right) {
                p_node->right = new node(value);
                m_size++;
                break;
            }
            else if(value < p_node->value && !p_node->left){
                p_node->left = new node(value);
                m_size++;
                break;
            }
            else if(value > p_node->value && p_node->right) {
                p_node = p_node->right;
            }
            else if(value < p_node->value && p_node->left) {
                p_node = p_node->left;
            }
        }
    }

private:
    struct node {
        T value;
        node* left;
        node* right;
        
        node(const T& val)
            : value(val)
            , left(nullptr)
            , right(nullptr) {
        }
    };
    
    node* mp_root;
    std::size_t m_size;
};

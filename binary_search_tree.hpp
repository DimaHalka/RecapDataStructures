#pragma once

#include "linked_list.hpp"
#include "pair.hpp"

template <typename T>
class binary_search_tree {
public:
    binary_search_tree()
        : mp_root(nullptr)
        , m_size(0) {
    }
 
    ~binary_search_tree() noexcept {
        std::function<void(node*)> recursive_delete;
        recursive_delete = [&](node* p_node){
            if(p_node){
                recursive_delete(p_node->left);
                recursive_delete(p_node->right);
                delete p_node;
            }
        };
        recursive_delete(mp_root);
        mp_root = nullptr;
        m_size = 0;
    }
    
    binary_search_tree(const binary_search_tree& other)
        : mp_root(nullptr)
        , m_size(0)
    {
        // TODO: if new throws existing nodes will leak, consider unique_ptr
        std::function<node*(node*)> recursive_clone;
        recursive_clone = [&](const node* p_source_node) -> node* {
            if(p_source_node) {
                node* p_new_node = new node(p_source_node->value);
                p_new_node->left = recursive_clone(p_source_node->left);
                p_new_node->right = recursive_clone(p_source_node->right);
                return p_new_node;
            }
            else {
                return nullptr;
            }
        };
        mp_root = recursive_clone(other.mp_root);
        m_size = other.m_size;
    }

    binary_search_tree& operator=(const binary_search_tree& other) {
        if(this != &other){
            binary_search_tree bst(other);
            std::swap(this->mp_root, bst.mp_root);
            std::swap(this->m_size, bst.m_size);
        }
        return *this;
    }

    binary_search_tree(binary_search_tree&&) {
        throw 0; // move ctor
    }

    binary_search_tree& operator=(binary_search_tree&&) {
        throw 0; // move op
    }
    
    bool operator==(const binary_search_tree& other) const noexcept {
        if(m_size != other.m_size)
            return false;
        
        std::function<bool(const node*, const node*)> recursive_compare;
        recursive_compare = [&](const node* p_node1, const node* p_node2) -> bool {
            if(!p_node1 && !p_node2)
                return true;
            if(p_node1 && !p_node2)
                return false;
            if(!p_node1 && p_node2)
                return false;
            if(p_node1->value != p_node2->value)
                return false;
            if(!recursive_compare(p_node1->left, p_node2->left))
                return false;
            if(!recursive_compare(p_node1->right, p_node2->right))
                return false;
            return true;            
        };
        return recursive_compare(mp_root, other.mp_root);
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

    [[nodiscard]] bool contains(const T& value) const noexcept {
         const node* p = mp_root;
         while (p) {
             if (value == p->value) return true;
             p = (value < p->value) ? p->left : p->right;
         }
         return false;
    }
    
    bool remove(const T& value) {
        node* parent = nullptr;
        node* cur = mp_root;
        bool is_right = false;

        while (cur && cur->value != value) {
            parent = cur;
            if (value < cur->value) {
                is_right = false;
                cur = cur->left;
            } else {
                is_right = true;
                cur = cur->right;
            }
        }
        if (!cur) return false;

        auto relink_parent = [&](node* new_child) {
            if (!parent) {
                mp_root = new_child;
            } else if (is_right) {
                parent->right = new_child;
            } else {
                parent->left = new_child;
            }
        };

        if (!cur->left && !cur->right) {
            relink_parent(nullptr);
            delete cur;
            --m_size;
            return true;
        }
        if (!cur->left) {
            relink_parent(cur->right);
            delete cur;
            --m_size;
            return true;
        }
        if (!cur->right) {
            relink_parent(cur->left);
            delete cur;
            --m_size;
            return true;
        }

        node* succ_parent = cur;
        node* succ = cur->right;
        bool succ_is_right = true;
        while (succ->left) {
            succ_parent = succ;
            succ = succ->left;
            succ_is_right = false;
        }

        cur->value = succ->value;
        node* succ_child = succ->right;
        if (succ_is_right) {
            succ_parent->right = succ_child;
        } else {
            succ_parent->left = succ_child;
        }
        delete succ;
        --m_size;
        return true;
    }

    
    template<typename Func>
    void traverse_bfs(Func&& func) const {
        if(!mp_root)
            return;
        
        linked_list<node*> queue;
        queue.push_back(mp_root);
        while(!queue.empty()) {
            node* p_node = queue.pop_front();
            if(p_node->left)
                queue.push_back(p_node->left);
            if(p_node->right)
                queue.push_back(p_node->right);
            func(p_node->value);
        }
    }
     
    template<typename Func>
    void traverse_inorder(Func&& func) const {
        std::function<void(const node*)> _traverse;
        _traverse = [&](const node* p_node){
            if(p_node) {
                _traverse(p_node->left);
                func(p_node->value);
                _traverse(p_node->right);
            }
        };
        _traverse(mp_root);
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

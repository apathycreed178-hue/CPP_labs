#ifndef LEFT_PRIORITY_QUEUE_H
#define LEFT_PRIORITY_QUEUE_H
#include "mergeable_priority_queue.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

class left_priority_queue : public mergeable_priority_queue {
private:
    struct node {
        int _priority;
        char * _value;
        node* left_subtree;
        node* right_subtree;
        int _dist;
    };

private:
    int (*_priority_comparer) (int, int);
	size_t _values_count;
	node* _root;

private:
    static void delete_leftists_trees(node*tree_root) {
        if (tree_root == nullptr) {
            return;
        }

        delete_leftists_trees(tree_root->left_subtree);
        delete_leftists_trees(tree_root->right_subtree);

        if (tree_root->_value != nullptr) {
            delete[] tree_root->_value;
            tree_root->_value = nullptr;
        }

        delete tree_root;
    }

    static node* copy_leftist_trees(node const* tree_root) {
        if (tree_root == nullptr) {
            return nullptr;
        }

        node* new_node = new node;
        new_node->_priority = tree_root->_priority;

        if (tree_root->_value != nullptr) {
            size_t len = strlen(tree_root->_value);
            new_node->_value = new char[len + 1];
            strcpy(new_node->_value, tree_root->_value);
        } else {
            new_node->_value = nullptr;
        }

        new_node->left_subtree = copy_leftist_trees(tree_root->left_subtree);
        new_node->right_subtree = copy_leftist_trees(tree_root->right_subtree);

        new_node->_dist = tree_root->_dist;

        return new_node;
    }

    node* merge_nodes(node* a, node* b) const {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        
        if (_priority_comparer(b->_priority, a->_priority) > 0) {
            std::swap(a, b);
        }
        a->right_subtree = merge_nodes(a->right_subtree, b);
        
        if (get_dist(a->left_subtree) < get_dist(a->right_subtree)) {
            std::swap(a->left_subtree, a->right_subtree);
        }
        
        a->_dist = get_dist(a->right_subtree) + 1;
        
        return a;
    }

    int get_dist(node* n) const {
        return n ? n->_dist : 0;
    }

public:
    //конструктор
    left_priority_queue(int (*comparer)(int, int)) : _priority_comparer(comparer), _values_count(0), _root(nullptr) {};
    //деструктор
    ~left_priority_queue();
    left_priority_queue(const left_priority_queue& other);
    left_priority_queue& operator=(const left_priority_queue& other);

    //функционал

    void insert(int p, char const* val);
    void merge(mergeable_priority_queue* to_merge_from);
	mergeable_priority_queue* meld(mergeable_priority_queue const* to_meld_with) const;

    char* get_max();
    char* remove_max();

};


//деструктор
left_priority_queue::~left_priority_queue() {
    delete_leftists_trees(_root);
    _values_count = 0;
    _priority_comparer = nullptr;
}
//конструктор копирования
left_priority_queue::left_priority_queue(const left_priority_queue& other) : 
    _root(copy_leftist_trees(other._root)), _values_count(other._values_count),
    _priority_comparer(other._priority_comparer) {

}
// оператор=
left_priority_queue& left_priority_queue::operator=(const left_priority_queue& other) {
    if (this == &other) {
        return *this;
    }

    delete_leftists_trees(this->_root);

    _root = copy_leftist_trees(other._root);
    _values_count = other._values_count;
    _priority_comparer = other._priority_comparer;

    return *this;
}

//merge
void left_priority_queue::merge(mergeable_priority_queue* to_merge_from) {
    left_priority_queue* other = dynamic_cast<left_priority_queue*>(to_merge_from);
    if (other == nullptr) {
        throw std::invalid_argument("Can't merge: invalid type of argument");
    }
    if (other->_root == nullptr) {
        return;
    }
    
    _root = merge_nodes(_root, other->_root);
    
    _values_count += other->_values_count;

    other->_root = nullptr;
    other->_values_count = 0;
}

//insert()
void left_priority_queue::insert(int priority, char const* value) {
    node* n = new node;

    n->_priority = priority;
    n->_value = new char[strlen(value)+1];
    strcpy(n->_value, value);
    n->left_subtree = n->right_subtree = nullptr;
    n->_dist = 1;
    _root = merge_nodes(_root, n);
    _values_count++;

}

mergeable_priority_queue* left_priority_queue::meld(mergeable_priority_queue const* to_meld_with) const {
    auto other = dynamic_cast<const left_priority_queue*>(to_meld_with);
    if (!other) throw std::invalid_argument("Can't merge: invalid type of argument");
    left_priority_queue* result = new left_priority_queue(_priority_comparer);

    node* copy1 = copy_leftist_trees(_root);
    node* copy2 = copy_leftist_trees(other->_root);
    result->_root = merge_nodes(copy1, copy2);
    result->_values_count = _values_count + other->_values_count;
    return result;
}

char* left_priority_queue::get_max() {
    if (_root == nullptr) {
        throw std::invalid_argument("Can't get max: queue is empty");
    }
    return this->_root->_value;
}
char* left_priority_queue::remove_max() {
    if (_root == nullptr) throw std::invalid_argument("empty");
    char* max_value = _root->_value;
    node* old_root = _root;
    _root = merge_nodes(_root->left_subtree, _root->right_subtree);
    delete old_root;
    --_values_count;
    return max_value;
}



#endif
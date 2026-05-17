#ifndef LEFT_PRIORITY_QUEUE_H
#define LEFT_PRIORITY_QUEUE_H
#include "mergeable_priority_queue.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

class left_priority_queue final : public mergeable_priority_queue {
private:
    struct node {
        int _priority;
        char * _value;
        node* left_subtree;
        node* right_subtree;
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
            return;
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

        return new_node;
    }

public:
    //конструктор
    left_priority_queue(int (*comparer)(int, int)) : _priority_comparer(comparer), _values_count(0) {};
    //деструктор
    ~left_priority_queue();
    left_priority_queue(const left_priority_queue& other);
    left_priority_queue& operator=(const left_priority_queue& other);

    //функционал

    void insert(int p, char* val);
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

//insert
void left_priority_queue::insert(int priority, char * value) {
    return;
}

//merge
void left_priority_queue::merge(mergeable_priority_queue* to_merge_from) {
    left_priority_queue* lpq_to_merge_from;
    if ((lpq_to_merge_from = dynamic_cast<left_priority_queue*>(to_merge_from)) == nullptr) {
        throw std::invalid_argument("Can't merge: invalid type of argument");
    }

    if (lpq_to_merge_from->_root == nullptr) {
        return;
    }

    if (this->_root == nullptr && lpq_to_merge_from->_root != nullptr) {
        this->_root = lpq_to_merge_from->_root;
        this->_values_count = lpq_to_merge_from->_values_count;
        lpq_to_merge_from->_root = nullptr;
        lpq_to_merge_from->_values_count = 0;
    }

    size_t merged_v_c = this->_values_count + lpq_to_merge_from->_values_count;
    size_t max_trees_count = 0;
}

//TODO - merge, meld, insert, remove_max

char* left_priority_queue::get_max() {
    return this->_root->_value;
}
char* left_priority_queue::remove_max() {
    return "A";
}



#endif
#ifndef SKEW_PRIORITY_QUEUE_H
#define SKEW_PRIORITY_QUEUE_H
#include <stdexcept>
#include "left_priority_queue.h"
#pragma warning( disable : 4996)

class skew_priority_queue final: public left_priority_queue {
public:
    // Конструктор
    skew_priority_queue(int (*comparer)(int, int))
        : left_priority_queue(comparer) {
    }

    // Конструктор копирования
    skew_priority_queue(const skew_priority_queue& other)
        : left_priority_queue(other) 
    {

    }

    // Оператор присваивания
    skew_priority_queue& operator=(const skew_priority_queue& other) {
        if (this != &other) {
            left_priority_queue::operator=(other); 
        }
        return *this;
    }

    // Деструктор
    ~skew_priority_queue() {

    }

protected:
    node* merge_nodes(node* a, node* b) const {
        if (!a) return b;
        if (!b) return a;
        if (_priority_comparer(b->_priority, a->_priority) > 0) std::swap(a, b);
        a->right_subtree = merge_nodes(a->right_subtree, b);
        std::swap(a->left_subtree, a->right_subtree);
        return a;
    }

};

#endif
#ifndef SKEW_PRIORITY_QUEUE_H
#define SKEW_PRIORITY_QUEUE_H
#include <stdexcept>
#include "left_priority_queue.h"
#pragma warning( disable : 4996)

class skew_priority_queue final : public left_priority_queue {
public:

    //конструктор
    skew_priority_queue(int (*comparer)(int, int))
        : left_priority_queue(comparer) {

    }

    //конструктор копирования
    skew_priority_queue(const skew_priority_queue& other)
        : left_priority_queue(dynamic_cast<left_priority_queue const &>(other))
    {

    }

    //оператор присваивания
    skew_priority_queue& operator=(const skew_priority_queue& other) {
        if (this != &other) {
            left_priority_queue::operator=(dynamic_cast<left_priority_queue const &>(other)); 
        }
        return *this;
    }

    //деструктор
    ~skew_priority_queue() {

    }

    mergeable_priority_queue* meld(mergeable_priority_queue const* to_meld_with) const override {
        auto other = dynamic_cast<const skew_priority_queue *>(to_meld_with);
        if (!other) throw std::invalid_argument("Can't merge: invalid type of argument");
        skew_priority_queue* result = new skew_priority_queue(_priority_comparer);

        node* copy1 = copy_leftist_trees(_root);
        node* copy2 = copy_leftist_trees(other->_root);
        result->_root = merge_nodes(copy1, copy2);
        result->_values_count = _values_count + other->_values_count;
                
        return result;
    }

private:
    virtual void keep_leftist(node * n) const override {

    }
};

#endif

#ifndef FIB_PRIORITY_QUEUE_H
#define FIB_PRIORITY_QUEUE_H
#include "binomial_priority_queue.h"
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#pragma warning(disable: 4996)

class fib_priority_queue final : public binomial_priority_queue {
public:

    //конструктор
    fib_priority_queue(int (*priority_comparer)(int, int))
        : binomial_priority_queue(priority_comparer) {

    }

    //конструктор копирования
    fib_priority_queue(const fib_priority_queue& other)
        : binomial_priority_queue(dynamic_cast<binomial_priority_queue const&>(other)) {

    }

    //оператор присваивания
    fib_priority_queue& operator=(const fib_priority_queue& other) {
        if (this != &other) {
            binomial_priority_queue::operator=(dynamic_cast<binomial_priority_queue const&>(other));
        }

        return *this;
    }

    //деструктор
    ~fib_priority_queue() {

    }

    void insert( int priority, char const* value) override {
		fib_priority_queue new_heap(_priorities_comparer);
		new_heap._root = create_node(priority, value);
		new_heap._root->brother = new_heap._root;
		new_heap._values_count = 1;

		merge(&new_heap);
	}

    void merge(mergeable_priority_queue* to_merge_from) override {

        fib_priority_queue* fib_to_merge_from;

        if ((fib_to_merge_from = dynamic_cast<fib_priority_queue*>(to_merge_from)) == nullptr) {
            throw std::invalid_argument("Parameter must be fib_priority_queue*");
        }

        if (this == to_merge_from) {
            return;
        }

        if (fib_to_merge_from->_root == nullptr) {
            return;
        }

        if (this->_root == nullptr && fib_to_merge_from != nullptr) {
            this->_root = fib_to_merge_from->_root;
            this->_values_count = fib_to_merge_from->_values_count;
            fib_to_merge_from->_root = nullptr;
            fib_to_merge_from->_values_count = 0;

            return;
        }

        size_t new_values_count = this->_values_count + fib_to_merge_from->_values_count;
        fib_to_merge_from->_values_count = 0;

        node* tmp = this->_root->brother;
        _root->brother = fib_to_merge_from->_root;
        node* tmp2 = fib_to_merge_from->_root;

        while (tmp2->brother != fib_to_merge_from->_root) {
            tmp2 = tmp2->brother;
        }

        tmp2->brother = tmp;

        this->_root = (_priorities_comparer(this->_root->priority, fib_to_merge_from->_root->priority) > 0)
            ? this->_root : fib_to_merge_from->_root;

        _values_count = new_values_count;
        fib_to_merge_from->_values_count = 0;
        fib_to_merge_from->_root = nullptr;
    }

    void consolidate() {
        if (_root == nullptr) {
            return;
        }

        fib_priority_queue tmp(*this);
        _values_count = 0;

        binomial_priority_queue* binomial_tmp = static_cast<binomial_priority_queue*>(&tmp);
        binomial_priority_queue::merge(binomial_tmp);
    }

    mergeable_priority_queue* meld(mergeable_priority_queue const* to_meld_with) const override {
        auto const* fib_to_meld = dynamic_cast<fib_priority_queue const*>(to_meld_with);
        if (!fib_to_meld) {
            throw std::invalid_argument("Parameter must be fib_priority_queue const*");
        }

        fib_priority_queue* result = new fib_priority_queue(*this);  // копия текущей
        fib_priority_queue temp(*fib_to_meld);                  // копия другой
        result->merge(&temp);                               // слияние
        return result;
    }

    char* remove_max() override{
        if (_root == nullptr) {
            throw std::invalid_argument("Can't delete element from empty queue");
        }

        node* tree_to_split = _root;

        if (tree_to_split->brother == tree_to_split) {
            _root = nullptr;
        }
        else {
            node* new_max_tree = tree_to_split->brother;
            node* runner = tree_to_split->brother;
            while (runner->brother != _root)
            {
                if (_priorities_comparer(runner->priority, new_max_tree->priority) > 0)
                {
                    new_max_tree = runner;
                }
                runner = runner->brother;
            }
            runner->brother = runner->brother->brother;
            _root = new_max_tree;
        }

        _values_count -= (1 << get_rank(tree_to_split));

        fib_priority_queue new_heap(_priorities_comparer);
        new_heap._root = tree_to_split->children;
        new_heap._values_count = (1 << get_rank(tree_to_split)) - 1;

        char* to_return = tree_to_split->value;

        delete tree_to_split;

        merge(&new_heap);

        consolidate();

        return to_return;

    }

};

#endif

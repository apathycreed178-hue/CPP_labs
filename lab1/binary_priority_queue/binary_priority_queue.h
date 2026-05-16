#ifndef BINARY_PRIORITY_QUEUE_H
#define BINARY_PRIORITY_QUEUE_H
#pragma warning(disable: 4996)
#pragma warning(disable: 6386)

#include "mergeable_priority_queue.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

class binary_priority_queue final: public mergeable_priority_queue {
	
private:
	struct node {
		char* value;
		int priority;
	};


private:
	int (*priority_comparer) (int, int);
	size_t values_count;
	node* priority_queue_;

private:
	void siftUp( size_t i);
	void siftDown(node* node_, size_t i);

public:

	void dump() const;

	//конструктор
	binary_priority_queue(int (*comparer)(int, int)) : priority_comparer(comparer), values_count(0), priority_queue_(nullptr) {};
	//деструктор
	~binary_priority_queue() { delete[] priority_queue_; };
	//TODO: конструктор копирования, оператор=
	binary_priority_queue(const binary_priority_queue& other) : priority_comparer(other.priority_comparer), values_count(other.values_count) {
		priority_queue_ = new node[values_count];
		for (size_t i = 0; i < values_count; ++i) {
			priority_queue_[i].priority = other.priority_queue_[i].priority;
			priority_queue_[i].value = new char[strlen(other.priority_queue_[i].value) + 1];
			strcpy(priority_queue_[i].value, other.priority_queue_[i].value);
		}
	}

	binary_priority_queue& operator=(const binary_priority_queue& other) {
		if (this == &other) {
			return *this;
		}

		delete[] priority_queue_;

		priority_comparer = other.priority_comparer;
		values_count = other.values_count;
		priority_queue_ = new node[values_count];
		for (size_t i = 0; i < values_count; ++i) {
			priority_queue_[i].priority = other.priority_queue_[i].priority;
			priority_queue_[i].value = new char[strlen(other.priority_queue_[i].value) + 1];
			strcpy(priority_queue_[i].value, other.priority_queue_[i].value);
		}

		return *this;
	}

	//функционал
	void insert(int priority_, const char* value_);
	void merge(mergeable_priority_queue* to_merge_from);
	mergeable_priority_queue* meld(mergeable_priority_queue const* to_meld_with) const;
	char* remove_max();
	char const* get_max();

private:
	static node* createNode(
		int priority,
		char const* value)
	{
		node* result = new node;
		result->priority = priority;
		result->value = new char[strlen(value) + 1];
		strcpy(result->value, value);
		return result;
	}
};

void binary_priority_queue::siftDown(node* node_, size_t i) {
	size_t largest = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;

	if (left < values_count && priority_queue_[left].priority > priority_queue_[largest].priority) {
		largest = left;
	}
	if (right < values_count && priority_queue_[right].priority > priority_queue_[largest].priority) {
		largest = right;
	}

	if (largest != i) {
		std::swap(priority_queue_[i], priority_queue_[largest]);
		siftDown(&priority_queue_[largest], largest);
	}
}

void binary_priority_queue::siftUp( size_t i) {
	if (i == 0) { return; }

	size_t parent = (i - 1) / 2;

	if (priority_comparer(priority_queue_[parent].priority, priority_queue_[i].priority) > 0) {
		std::swap(priority_queue_[i], priority_queue_[parent]);
		siftUp(parent);
	}

}

void binary_priority_queue::insert(int priority_, const char* value_) {
	size_t newSize = values_count + 1;
	node* newNode = createNode(priority_, value_);

	node* freshQueue = new node[newSize];
	if (priority_queue_) {
		for (size_t i = 0; i < values_count; i++)
			freshQueue[i] = priority_queue_[i];
		delete[] priority_queue_;
	}

	freshQueue[values_count] = *newNode;
	delete newNode;
	priority_queue_ = freshQueue;
	values_count = newSize;

	siftUp( values_count - 1);
}

void binary_priority_queue::merge(mergeable_priority_queue* to_merge_from) {
	binary_priority_queue* binary_pq_to_merge_from = dynamic_cast<binary_priority_queue*>(to_merge_from);

	if (!binary_pq_to_merge_from) {
		throw std::invalid_argument("Can't merge: incompatible types");
	}

	if ( this == binary_pq_to_merge_from) {
		return;
	}

	if (binary_pq_to_merge_from->values_count == 0) {
		return;
	}

	for (size_t i = 0; i < binary_pq_to_merge_from->values_count; i++) {
		insert(binary_pq_to_merge_from->priority_queue_[i].priority, binary_pq_to_merge_from->priority_queue_[i].value);
	}
}


mergeable_priority_queue* binary_priority_queue::meld(mergeable_priority_queue const* to_meld_with) const {
	
	binary_priority_queue const * bi_to_meld_from;
	if ((bi_to_meld_from = dynamic_cast<binary_priority_queue const *>(to_meld_with)) == nullptr) {
		throw std::invalid_argument("Can't meld: incompatible types");
	}

	binary_priority_queue* h1 = new binary_priority_queue(*this);
	binary_priority_queue h2(*bi_to_meld_from);
	h1->merge(&h2);

	return h1;
}
char* binary_priority_queue::remove_max() {
	if (values_count == 0) {
		throw std::out_of_range("Can't remove max: queue is empty");
	}

	char* max_value = new char[strlen(priority_queue_[0].value) + 1];
	strcpy(max_value, priority_queue_[0].value);

	std::swap(priority_queue_[0], priority_queue_[values_count - 1]);
	values_count--;

	siftDown(priority_queue_, 0);

	return max_value;
}
char const* binary_priority_queue::get_max() {
	return priority_queue_[0].value;
}
//removeMax

void binary_priority_queue::dump() const {
	for (size_t i = 0; i < values_count; ++i) {
		std::cout << "index " << i << ": data=" << priority_queue_[i].value
			<< " priority=" << priority_queue_[i].priority << std::endl;
	}
}

#endif
#ifndef BINARY_PRIORITY_QUEUE_H
#define BINARY_PRIORITY_QUEUE_H
#pragma warning(disable: 4996)
#pragma warning(disable: 6386)

#include "mergeable_priority_queue.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

class binary_priority_queue final: public mergeable_priority_queue {

	//a.добавление значения типа char* по ключу типа int в приоритетную очередь
	//b.поиск значения по наиболее приоритетному ключу
	//c.удаление значения по наиболее приоритетному ключу
	//d.слияние двух приоритетных очередей в вызывающий объект приоритетной очереди


private:
	struct node {
		char* value;
		int priority;
	};

public:
	class empty_priority_queue_exception : public std::exception {
	public:
		char const* what() const override {
			return "Can't get/remove maximum from priority queue";
		}

	};

private:
	int (*priority_comparer) (int, int);
	size_t values_count;
	node* priority_queue;

private:
	void siftUp( size_t i);
	void siftDown(node* node_, size_t i);

public:

	void dump() const;

	//конструктор
	binary_priority_queue(int (*comparer)(int, int)) : priority_comparer(comparer), values_count(0), priority_queue(nullptr) {};
	//деструктор
	~binary_priority_queue() { delete[] priority_queue; };
	//TODO: конструктор копирования, оператор=

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

	if (left < values_count && priority_queue[left].priority > priority_queue[largest].priority) {
		largest = left;
	}
	if (right < values_count && priority_queue[right].priority > priority_queue[largest].priority) {
		largest = right;
	}

	if (largest != i) {
		std::swap(priority_queue[i], priority_queue[largest]);
		siftDown(&priority_queue[largest], largest);
	}
}

void binary_priority_queue::siftUp( size_t i) {
	if (i == 0) { return; }

	size_t parent = (i - 1) / 2;

	if (priority_comparer(priority_queue[parent].priority, priority_queue[i].priority) > 0) {
		std::swap(priority_queue[i], priority_queue[parent]);
		siftUp(parent);
	}

}

void binary_priority_queue::insert(int priority_, const char* value_) {
	size_t newSize = values_count + 1;
	node* newNode = createNode(priority_, value_);

	node* freshQueue = new node[newSize];
	if (priority_queue) {
		for (size_t i = 0; i < values_count; i++)
			freshQueue[i] = priority_queue[i];
		delete[] priority_queue;
	}

	freshQueue[values_count] = *newNode;
	delete newNode;
	priority_queue = freshQueue;
	values_count = newSize;

	siftUp( values_count - 1);
}

void binary_priority_queue::merge(mergeable_priority_queue* to_merge_from) {
	return;
}
mergeable_priority_queue* binary_priority_queue::meld(mergeable_priority_queue const* to_meld_with) const {
	binary_priority_queue* n = new binary_priority_queue(*this);
	return n;
}
char* binary_priority_queue::remove_max() {
	return priority_queue[0].value;
}
char const* binary_priority_queue::get_max() {
	return "000";
}
//getMax
//removeMax
//insert
//merge
//meld

void binary_priority_queue::dump() const {
	for (size_t i = 0; i < values_count; ++i) {
		std::cout << "index " << i << ": data=" << priority_queue[i].value
			<< " priority=" << priority_queue[i].priority << std::endl;
	}
}

#endif
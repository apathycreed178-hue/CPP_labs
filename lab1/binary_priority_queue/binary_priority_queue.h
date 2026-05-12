#ifndef BINARY_PRIORITY_QUEUE_H
#define BINARY_PRIORITY_QUEUE_H
#pragma warning(disable: 4996)

#include "mergeable_priority_queue.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

class binary_priority_queue : public mergeable_priority_queue {

	//a.добавление значения типа char* по ключу типа int в приоритетную очередь
	//b.поиск значения по наиболее приоритетному ключу
	//c.удаление значения по наиболее приоритетному ключу
	//d.слияние двух приоритетных очередей в вызывающий объект приоритетной очереди


private:
	struct node {
		char* value;
		int priority;
		node* brother;
		node* children;
	};

public:

	class empty_priority_queue_exception : public std::exception {
	public:

		char const* what() const override
		{
			return "Can't get/remove maximum from priority queue";
		}

	};

private:

	node* _root;
	int (*priority_comparer) (int, int);
	size_t _values_count;


};

#endif
#include <iostream>
#include "binary_priority_queue.h"

int higherPriority(int p1, int p2);

int main()
{

    binary_priority_queue queue(higherPriority);
    binary_priority_queue queue2(higherPriority);
    
    const char* values[] ={"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

    for (int i = 0; i < 10; i++) {
        queue.insert(rand() % 100 + 1, values[rand() % 10]);
        queue2.insert(rand() % 100 + 1, values[rand() % 10]);
    }

    std::cout << "=============================================" << std::endl;

    std::cout << "Max using get_max(): " << queue.get_max() << std::endl;

    std::cout << "=============================================" << std::endl;

    std::cout << "Printing priority queue: " << std::endl;
    queue.dump();

    std::cout << "=============================================" << std::endl;

    std::cout << "Removing max: " << queue.remove_max() << std::endl;

    std::cout << "=============================================" << std::endl;

    std::cout << "Printing priority queue: " << std::endl;
    queue.dump();

    std::cout << "=============================================" << std::endl;

    std::cout << "Merging queue2 into queue: " << std::endl;
    queue.merge(&queue2);

    std::cout << "=============================================" << std::endl;

    queue.dump();

    binary_priority_queue* melded_queue = dynamic_cast<binary_priority_queue*>(queue.meld(&queue2));
    std::cout << "=============================================" << std::endl;
    std::cout << "Melded queue: " << std::endl;
    std::cout << "=============================================" << std::endl;
    melded_queue->dump();

}


int higherPriority(int p1, int p2) {
    return p2 - p1;
}
#include <iostream>
#include "left_priority_queue.h"

int priorityCMP(int, int);

int main() {

    const char* values[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

    left_priority_queue myQueue(priorityCMP);

    for (int i = 0; i < 30; ++i) {
        myQueue.insert(rand() % 100 + 1, values[rand() % 10]);
    }

    std::cout << "Max: " << myQueue.get_max() << std::endl;

    return 0;
}

int priorityCMP(int p1, int p2) {
    return p1 - p2;
}
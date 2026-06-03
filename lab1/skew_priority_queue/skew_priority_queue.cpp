#include <iostream>
#include <stdexcept> 
#include "skew_priority_queue.h"

int priorityCMP(int, int);

int main() {

    const char* values[10] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };

    skew_priority_queue myQueue(priorityCMP);
    skew_priority_queue anotherQueue(priorityCMP);

    for (int i = 0; i < 10; ++i) {
        int cur_pri = rand() % 100 + 1;
        char const * cur_val = values[rand() % 10];

        myQueue.insert(cur_pri, cur_val);
        std::cout << cur_pri << " ";

        anotherQueue.insert(rand() % 100 + 1, values[rand() % 10]);
    }

    std::cout << "=============================================" << std::endl << std::endl;
    std::cout << "Current queue: " << std::endl;

    myQueue.print_queue();
    std::cout << "=============================================" << std::endl;

    std::cout << "Max: " << myQueue.get_max() << std::endl;

    std::cout << "=============================================" << std::endl;

    std::cout << "Removed max: " << myQueue.remove_max() << std::endl;

    std::cout << "=============================================" << std::endl << std::endl; ;

    std::cout << "Current queue: " << std::endl;

    myQueue.print_queue();
    std::cout << "=============================================" << std::endl << std::endl;;

    std::cout << "Merged q1 and q2: " << std::endl;

    myQueue.merge(&anotherQueue);
    myQueue.print_queue();
    std::cout << "=============================================" << std::endl;

    skew_priority_queue* oneMoreQueue;
    oneMoreQueue = dynamic_cast<skew_priority_queue*>(myQueue.meld(&anotherQueue));

    std::cout << "Melded q1 and q2(for now it is empty) to another queue: " << std::endl << std::endl;
    oneMoreQueue->print_queue();
    std::cout << "=============================================" << std::endl;

    try {
        anotherQueue.get_max(); // пустая после merge
    }
    catch (const std::logic_error& ex) {
        std::cout << "ERR: " << ex.what() << std::endl;
    }


    return 0;
}

int priorityCMP(int p1, int p2) {
    return p1 - p2;
}

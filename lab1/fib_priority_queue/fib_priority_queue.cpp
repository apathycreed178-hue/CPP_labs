#include <iostream>
#include <stdexcept> 
#include "fib_priority_queue.h"
#include <typeinfo>

int priorityCMP(int, int);

int main() {

    const char* values[10] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };

    fib_priority_queue myQueue(priorityCMP);
    fib_priority_queue anotherQueue(priorityCMP);

    for (int i = 0; i < 10; ++i) {
        myQueue.insert(rand() % 100 + 1, values[rand() % 10]);
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

    fib_priority_queue* oneMoreQueue;
    oneMoreQueue = dynamic_cast<fib_priority_queue*>(myQueue.meld(&anotherQueue));

    std::cout << "Merlded q1 and q2(for now it is empty) to another queue: " << std::endl << std::endl;;
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

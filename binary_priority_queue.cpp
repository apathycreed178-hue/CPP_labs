#include <iostream>
#include "binary_priority_queue.h"

int higherPriority(int p1, int p2);

int main()
{

    binary_priority_queue queue(higherPriority);
    
    queue.insert(13, "aoaoia");
    queue.insert(1113, "aoa");
    queue.insert(1, "aoaa");
    queue.insert(12, "aoaoiaadafa");

    queue.dump();


}


int higherPriority(int p1, int p2) {
    return p2 - p1;
}
#include "binomial_priority_queue.h"
#include <stdexcept>
#pragma warning(disable: 4096)

void bpq_demo();
int priorities_comparer(int, int);

int main() {

    bpq_demo();

    return 0;
}

int priorities_comparer(int p1, int p2) {
    return p1 - p2;
}

void bpq_demo()
{

    std::cout << 1;
    
	srand((unsigned)time(NULL));

	binomial_priority_queue instance(priorities_comparer);

	binomial_priority_queue meld_from_all(priorities_comparer);

	char *removed_value;
	for (int i = 0; i < 250; i++)
	{
		switch (rand() % 1)
		{
		case 0:
			instance.insert(rand() % 9000 + 1000, "pukpuk");
			break;
		case 1:
			try
			{
				delete (removed_value = instance.remove_max());
			}
			catch (binomial_priority_queue::empty_priority_queue_exception const &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		}

		binomial_priority_queue *melded = dynamic_cast<binomial_priority_queue*>(meld_from_all.meld(&instance));
		meld_from_all = *melded;
		delete melded;

		std::cout << "instance: ";
		instance.debug_print();
		std::cout << "melded: ";
		meld_from_all.debug_print();
	}
}
#include <iostream>
#include "complexInteger.h"

int main() {

    complex_int myInt(1.0, 3.7);
	complex_int otherInt(2.0, 4.5);

	std::cout << "Integer a: " << myInt << std::endl;
	std::cout << "Integer b: " << otherInt << std::endl;
	
	std::cout << std::endl << "============================================================" << std::endl << std::endl;

	std::cout << "Result of a + b: " <<  myInt + otherInt << std::endl;
	std::cout << "Result of a - b: " << myInt - otherInt << std::endl;

	std::cout << std::endl << "============================================================" << std::endl << std::endl;

	std::cout << "Result of a * b: " << myInt * otherInt << std::endl;
	std::cout << "Result of a / b: " << myInt / otherInt << std::endl;

	std::cout << std::endl << "============================================================" << std::endl << std::endl;

	std::cout << "Module of a: " << myInt.get_module() << std::endl;
	std::cout << "Argument of b: " << otherInt.get_arg() << std::endl;

	std::cout << std::endl << "============================================================" << std::endl << std::endl;

	complex_int inpInt;
	std::cin >> inpInt;

	std::cout << std::endl << "============================================================" << std::endl << std::endl;

	std::cout << "You entered: " << inpInt << std::endl;

	return 0;

}
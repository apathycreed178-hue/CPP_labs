#include <iostream>
#include "logic_values_array.h"



int main()
{
	char mystr[33];

	logic_values_array num1(42);
	logic_values_array num2(86);
	logic_values_array res;

	res.set_value((num1.conj(num2)).get_value());
	std::cout << "Num1 & Num2: " << res.get_value() << std::endl;

	res.set_value((num1.disj(num2)).get_value());
	std::cout << "Num1 | Num2: " << res.get_value() << std::endl;

	res.set_value((num1.invert()).get_value());
	std::cout << "not Num2: " << res.get_value() << std::endl;

	res.set_value((num1.imp(num2)).get_value());
	std::cout << "Num1 -> Num2: " << res.get_value() << std::endl;

	res.set_value((num1.coimp(num2)).get_value());
	std::cout << "Num1 <- Num2: " << res.get_value() << std::endl;

	res.set_value((num1.eq(num2)).get_value());
	std::cout << "Num1 = Num2: " << res.get_value() << std::endl;

	res.set_value((num1.x_disj(num2)).get_value());
	std::cout << "Num1 ^ Num2: " << res.get_value() << std::endl;

	res.set_value((num1.arrow(num2)).get_value());
	std::cout << "Num1 NOR Num2: " << res.get_value() << std::endl;

	res.set_value((num1.stroke(num2)).get_value());
	std::cout << "Num1 NAND Num2: " << res.get_value() << std::endl;

	std::cout << std::endl;
	std::cout << "=======================================================" << std::endl;
	std::cout << std::endl;

	std::cout << "Num1 == Num2 using equals(): " << res.equals(num1, num2) << std::endl;

	std::cout << std::endl;
	std::cout << "=======================================================" << std::endl;
	std::cout << std::endl;

	std::cout << "Num1 second bit: " << num1.get_bit(1) << std::endl;
	std::cout << "Num1 second bit using []: " << num1[1] << std::endl;

	std::cout << std::endl;
	std::cout << "=======================================================" << std::endl;
	std::cout << std::endl;

	num1.create_binary_field(mystr);
	std::cout << "Num1 as str: " << mystr << std::endl;

	return 0;
}
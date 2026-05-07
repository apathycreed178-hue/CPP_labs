#ifndef LOGIC_VALUES_ARRAY
#define LOGIC_VALUES_ARRAY
#include <stdexcept>
#pragma once

class logic_values_array {
	unsigned int _value;
public:
	// конструктор
	logic_values_array(unsigned int value = 0) { _value = value; };

	// сеттер и геттер
	void set_value(unsigned int value) { _value = value; };
	unsigned int get_value() const { return _value; };

	// методы логических операций

	logic_values_array conj(logic_values_array& other) const;
	logic_values_array disj(logic_values_array& other) const;
	logic_values_array invert() const;

	logic_values_array imp(logic_values_array& other) const;
	logic_values_array coimp(logic_values_array& other) const;
	logic_values_array eq(logic_values_array& other) const;

	logic_values_array x_disj(logic_values_array& other) const;

	logic_values_array arrow(logic_values_array& other) const;
	logic_values_array stroke(logic_values_array& other) const;

	// метод equals
	static bool equals(const logic_values_array& lhs, const logic_values_array& rhs) {
		return lhs._value == rhs._value;
	}

	// метод get_bit
	unsigned int get_bit(size_t index) const;
	// перегрузка []
	unsigned int operator[](int index) const;

	// метод create_binary_field
	void create_binary_field(char* field) const;
};

// !, &, |
logic_values_array logic_values_array::conj(logic_values_array& other) const {
	return logic_values_array(_value & other.get_value());
}
logic_values_array logic_values_array::disj(logic_values_array& other) const {
	return logic_values_array(_value | other.get_value());
}
logic_values_array logic_values_array::invert() const {
	return logic_values_array(~_value);
}
// импликация, коимпликация, эквивалентность, XOR
logic_values_array logic_values_array::imp(logic_values_array& other) const {
	return logic_values_array(~_value | other.get_value());
}
logic_values_array logic_values_array::coimp(logic_values_array& other) const {
	return logic_values_array(_value | ~other.get_value());
}
logic_values_array logic_values_array::eq(logic_values_array& other) const {
	return logic_values_array(~(_value & other.get_value()));
}
logic_values_array logic_values_array::x_disj(logic_values_array& other) const {
	return logic_values_array(_value ^ other.get_value());
}
// Cтрелка Пирса и шрих Шеффера
logic_values_array logic_values_array::arrow(logic_values_array& other) const {
	return logic_values_array(~(_value | other.get_value()));
}
logic_values_array logic_values_array::stroke(logic_values_array& other) const {
	return logic_values_array(~(_value & other.get_value()));
}


// get_bit
unsigned int logic_values_array::get_bit(size_t index) const {
	if ( index >= sizeof(unsigned int) * 8) {
		throw std::out_of_range("bit is out of range");
	}
	return (_value >> index) & 1U;
}
// оператор []
unsigned int logic_values_array::operator[](int index) const {
	return get_bit(index);
}

//create_binary_field
void logic_values_array::create_binary_field(char* field) const {
	const size_t bits = sizeof(unsigned int) * 8;

	for (size_t i = 0; i < bits; i++) {
		unsigned int bit = get_bit(bits - 1 - i);
		field[i] = bit ? '1' : '0';
	}

	field[bits] = '\0';
}

#endif
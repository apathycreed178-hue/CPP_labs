#ifndef COMPLEX_INT
#define COMPLEX_INT


class complex_int {
	double valid;
	double imaginary;
public:
	complex_int(double valid_ = 0.0, double imaginary_ = 0.0) { valid = valid_; imaginary = imaginary_; };

	// действия над КЧ
	complex_int& operator+=(const complex_int& other);
	complex_int operator+(complex_int myInt);

	complex_int& operator-=(const complex_int& other);
	complex_int operator-(complex_int myInt);

	complex_int& operator*=(const complex_int& other);
	complex_int operator*(complex_int myInt);

	complex_int& operator/=(const complex_int& other);
	complex_int operator/(complex_int myInt);

	// методы для получения модуля и аргумента
	double get_module() const;
	double get_arg() const;

	// перегрузка ввода и вывода
	friend std::ostream& operator<<(std::ostream& os, const complex_int& myInt);
	friend std::istream& operator>>(std::istream& is, complex_int& myInt);

	// деструктор 
	~complex_int() {};
};


// + & += overload
complex_int& complex_int::operator+=(const complex_int& other) {

	valid += other.valid;
	imaginary += other.imaginary;

	return *this;
}
complex_int complex_int::operator+(complex_int myInt) {
	complex_int result = *this;
	return result += myInt;
}

// - & -= overload
complex_int& complex_int::operator-=(const complex_int& other) {

	valid -= other.valid;
	imaginary -= other.imaginary;

	return *this;
}
complex_int complex_int::operator-(complex_int myInt) {
	complex_int result = *this;
	return result -= myInt;
}

// умножение двучленов ((a + bi)(c + di)) с учетом, что (i ^ 2 = -1).Формула: ((a + bi)(c + di) = (ac - bd) + (ad + bc)i)

// * & *= overload
complex_int& complex_int::operator*=(const complex_int& other) {

	valid = (other.valid * valid - other.imaginary*imaginary);
	imaginary = other.imaginary*valid + other.valid*imaginary;

	return *this;
}
complex_int complex_int::operator*(complex_int myInt) {
	complex_int result = *this;
	return result *= myInt;
}

// Деление комплексных чисел (a + bi)/(c + di) = ((ac + bd)/(c*c + d*d)) + ((bc - ad)i/(c*c + d*d))

// / & /= overload
complex_int& complex_int::operator/=(const complex_int& other) {

	if (other.valid == 0 && other.imaginary == 0) {
		throw std::runtime_error("ERROR: division by zero");
	}
	valid = (other.valid * valid + other.imaginary * imaginary) / (other.valid * other.valid + other.imaginary * other.imaginary);
	imaginary = (other.imaginary * valid - other.valid * imaginary) / (other.valid * other.valid + other.imaginary * other.imaginary);


	return *this;
}
complex_int complex_int::operator/(complex_int myInt) {
	complex_int result = *this;
	return result /= myInt;
}

// модуль комплексного числа
double complex_int::get_module() const {
	return sqrt(valid * valid + imaginary * imaginary);
}

// аргумент комплексного числа
double complex_int::get_arg() const {
	//TODO atan2
	return atan(imaginary / valid);
}

// << overload
std::ostream& operator<<(std::ostream& os, const complex_int& myInt) {
	if (myInt.valid != 0) {
		os << myInt.valid;
	}
	if (myInt.imaginary > 0) {
		os << "+" << myInt.imaginary << "i";
	}
	else if (myInt.imaginary < 0) {
		os << myInt.imaginary << "i";
	}

	return os;
}

// >> overload
std::istream& operator>>(std::istream& is, complex_int& myInt) {
	std::cout << "Enter the real part of the complex number: ";
	is >> myInt.valid;
	std::cout << "Enter the imaginary part of the complex number: ";
	is >> myInt.imaginary;
	return is;
}

#endif
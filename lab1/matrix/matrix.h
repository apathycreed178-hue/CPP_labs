#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdexcept>
#include <cmath>
#define EPS 1e-12

class matrix final {

	double** _matrix;
	size_t rows;
	size_t columns;

	void alloc_mem();
	void copy_matrix(const matrix& other);

public:

	struct I {
		size_t row = 0;
		size_t column = 0;
		I(size_t r, size_t c) { row = r; column = c; };
	};

public:
	// конструктор
	matrix(size_t _rows, size_t _columns);

	// правило трех
	matrix(const matrix& other);
	matrix& operator=(matrix other);
	~matrix();

	// перегрузка операторов
	matrix operator+(const matrix& other) const;
	matrix operator-(const matrix& other) const;
	matrix operator*(double num) const;
	friend matrix operator*(double num, matrix const &m) { return m * num; };
	matrix operator*(const matrix& other) const;

	// транспонирование
	matrix transpose() const;

	// определитель(Метод Гаусса)
	double getDeterminant() const;

	// обратная матрица
	matrix reverse() const;

	// вспомогательные
	double getElem(size_t _row, size_t _column) const;
	void setElem(size_t _row, size_t _column, double elem);
	void swap(matrix& other) noexcept;
	void swap(size_t r, size_t c) noexcept;

	// перегрузка []
	double& operator[]( matrix::I i);

	// псевдо-рандомное заполнение матрицы
	friend void setRandomElems(matrix& mtr, int r_i);

	friend void printMatrix(const matrix& mtr);

};

// выделение памяти
void matrix::alloc_mem() {
	_matrix = new double* [rows];

	try {
		for (size_t i = 0; i < rows; ++i) {
			_matrix[i] = new double[columns];
		}
	} catch (const std::bad_alloc&) {
	for (size_t k = 0; k < rows; ++k) {
		delete[] _matrix[k];
	}
	delete[] _matrix;
	_matrix = nullptr;
	throw;
}
}

// конструктор
matrix::matrix(size_t _rows, size_t _columns) {

	if (_rows == 0 || _columns == 0) {
		throw std::runtime_error("Can't create matrix with zero rows or columns");
	}

	rows = _rows;
	columns = _columns;
	_matrix = nullptr;

	try {
		alloc_mem();
	}
	catch (const std::bad_alloc&) {
		throw std::runtime_error("Memory error");
	}


	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < columns; j++) {
			_matrix[i][j] = 0.0;
		}
	}
}


// перегрузка операций
matrix matrix::operator+(const matrix& other) const {


	if (rows != other.rows || columns != other.columns) {
		throw std::invalid_argument("Can't summarize matrix with different size");
	}

	matrix result = *this;

	for (size_t i = 0; i < result.rows; i++) {
		for (size_t j = 0; j < result.columns; j++) {
			result._matrix[i][j] = result._matrix[i][j] + other._matrix[i][j];
		}
	}

	return result;
}
matrix matrix::operator-(const matrix& other) const {

	if (rows != other.rows || columns != other.columns) {
		throw std::invalid_argument("Can't summarize matrix with different size");
	}

	matrix result = *this;

	for (size_t i = 0; i < result.rows; i++) {
		for (size_t j = 0; j < result.columns; j++) {
			result._matrix[i][j] = result._matrix[i][j] - other._matrix[i][j];
		}
	}

	return result;
}
matrix matrix::operator*(double num) const {

	matrix result = *this;

	for (size_t i = 0; i < result.rows; i++) {
		for (size_t j = 0; j < result.columns; j++) {
			result._matrix[i][j] = result._matrix[i][j] * num;
		}
	}

	return result;
}
matrix matrix::operator*(const matrix& other) const {
	if (rows != other.columns) {
		throw std::runtime_error("Can't multiple matrix with different sizes: rows1 != columns2");
	}

	matrix result(rows, other.columns);

	for (size_t i = 0; i < rows; i++) {
		for (size_t j = 0; j < other.columns; j++) {
			double sum = 0.0;
			for (size_t k = 0; k < columns; k++) {
				sum += _matrix[i][k] * other._matrix[k][j];
			}
			result._matrix[i][j] = sum;
		}
	}

	return result;
}


// транспонирование
matrix matrix::transpose() const {

	matrix result(columns, rows);

	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			result._matrix[j][i] = this->_matrix[i][j];
		}
	}

	return result;
}

// оперделитель
double matrix::getDeterminant() const {
	if (rows != columns) {
		throw std::runtime_error("Determinant exists only for square matrix");
	}

	matrix tmp = *this;
	double det = 1.0;

	for (size_t i = 0; i < rows; i++) {

		int pivot_row = i;

		for (size_t j = i + 1; j < rows; j++) {
			if ( fabs(tmp._matrix[j][i]) > fabs(tmp._matrix[pivot_row][i])) {
				pivot_row = j;
			}
		}

		if (fabs(tmp._matrix[pivot_row][i]) < EPS) { return 0.0; }

		if (pivot_row != i) {
			tmp.swap(i, pivot_row);
			det = -det;
		}

		for (size_t j = i + 1; j < rows; j++) {
			double factor = tmp._matrix[j][i] / tmp._matrix[i][i];
			for (size_t k = i; k < rows; k++) {
				tmp._matrix[j][k] = tmp._matrix[j][k] - factor * tmp._matrix[i][k];
			}
		}

		det = det * tmp._matrix[i][i];

	}

	return det;
}

// обратная матрица
matrix matrix::reverse() const {
	if (rows != columns) {
		throw std::runtime_error("Can't make reverse for not-square matrix");
	}

	double det = getDeterminant();

	// если 0 определитель - возвращаем матрицу [ 0.0 ]
	if (fabs(det) < EPS) {
		throw std::runtime_error("Inverse matrix not exists");
	}

	// создаем расширенную матрицу
	matrix resized_matrix(rows, rows * 2);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < rows; ++j) {
			resized_matrix._matrix[i][j] = _matrix[i][j];
			resized_matrix._matrix[i][j + rows] = (i == j) ? 1.0 : 0.0;
		}
	}

	for (size_t i = 0; i < rows; ++i) {
		// Поиск главного элемента
		size_t pivot_row = i;
		for (size_t k = i + 1; k < rows; ++k) {
			if (fabs(resized_matrix._matrix[k][i]) > fabs(resized_matrix._matrix[pivot_row][i])) {
				pivot_row = k;
			}
		}

		if (fabs(resized_matrix._matrix[pivot_row][i]) < EPS) {
			return matrix(1, 1);
		}

		// Перестановка строк
		if (pivot_row != i) {
			std::swap(resized_matrix._matrix[i], resized_matrix._matrix[pivot_row]);
		}

		// Нормализация текущей строки
		double pivot = resized_matrix._matrix[i][i];
		for (size_t j = i; j < 2 * rows; ++j) {
			resized_matrix._matrix[i][j] /= pivot;
		}

		// Вычитание из остальных строк
		for (size_t k = 0; k < rows; ++k) {
			if (k != i) {
				double factor = resized_matrix._matrix[k][i];
				for (size_t j = i; j < 2 * rows; ++j) {
					resized_matrix._matrix[k][j] -= factor * resized_matrix._matrix[i][j];
				}
			}
		}
	}

	matrix result(rows, rows);
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < rows; ++j) {
			result._matrix[i][j] = resized_matrix._matrix[i][j + rows];
		}
	}

	return result;

}


// ПРАВИЛО ТРЕХ
// Деструктор
matrix::~matrix() {
	for (size_t k = 0; k < rows; ++k) {
		delete[] _matrix[k];
	}
	rows = 0;
	delete[] _matrix;
	_matrix = nullptr;
}

// конструктор копирования
matrix::matrix(const matrix& other) : rows(other.rows), columns(other.columns), _matrix(nullptr) {
	if (other.rows > 0 && other.columns > 0) {
		alloc_mem();
		copy_matrix(other);
	}
}

// Оператор присваивания
matrix& matrix::operator=(matrix other) {
	swap(other);
	return *this;
}

// Обмен содержимым
void matrix::swap(matrix& other) noexcept {
	std::swap(rows, other.rows);
	std::swap(columns, other.columns);
	std::swap(_matrix, other._matrix);
}
void matrix::swap(size_t r, size_t c) noexcept {
	double* tmp = _matrix[r];
	_matrix[r] = _matrix[c];
	_matrix[c] = tmp;
}

// Вспомогательные функции(приватные)
double matrix::getElem(size_t _row, size_t _column) const {
	return _matrix[_row][_column];
}
void matrix::setElem(size_t _row, size_t _column, double elem) {
	_matrix[_row][_column] = elem;
}

void matrix::copy_matrix(const matrix& other) {
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			_matrix[i][j] = other._matrix[i][j];
		}
	}
}
// перегрузка []
double& matrix::operator[]( matrix::I i) {
	return this->_matrix[i.row][i.column];
}

// рандомные элементы матрицы
void setRandomElems(matrix& mtr, int random_int) {
	for (size_t i = 0; i < mtr.rows; i++) {
		for (size_t j = 0; j < mtr.columns; j++) {
			mtr.setElem(i, j, (rand() % random_int + 1));
		}
	}
}
// принт матрицы
void printMatrix(const matrix& mtr) {
	for (size_t i = 0; i < mtr.rows; i++) {
		for (size_t j = 0; j < mtr.columns; j++) {
			std::cout << mtr.getElem(i, j) << " ";
		}
		std::cout << std::endl;
	}
}




#endif

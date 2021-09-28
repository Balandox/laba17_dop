#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <iostream>
#include <stdexcept>
#include "Point.h"

template <typename T>
class ProxyIndexer {
	T* rows;
	int columns;
public:
	ProxyIndexer(T* row, int colum) {
		this->rows = row;
		this->columns = colum;
	}
	T& operator[](size_t colum) {
		if ((colum - 1 < 0 || colum - 1 >= this->columns))
			throw std::out_of_range("Column out of range!");
		return this->rows[colum - 1];
	}
};

template <typename T>

class Matrix {
private:
	T** args;
	size_t rows;
	size_t columns;
public:
	friend class ProxyIndexer<T>;
	ProxyIndexer<T> operator[](size_t row) {
		if (row - 1 < 0 || row - 1 >= this->rows)
			throw std::out_of_range("Row out of range!");
		return ProxyIndexer <T> (this->args[row - 1], this->columns);
	}
	Matrix(size_t row, size_t column) {
		this->columns = column;
		this->rows = row;
		this->args = new T* [this->rows];
		for (size_t i = 0; i < this->rows; i++)
			this->args[i] = new T[this->columns];     
	}
	~Matrix() {
		for (size_t i = 0; i < this->rows; i++)
			delete[] this->args[i];
		delete[] this->args;
	}
	Matrix(const Matrix& m) {
		this->rows = m.rows;
		this->columns = m.columns;
		this->args = new T * [this->rows];
		for (size_t i = 0; i < this->rows; i++)
			this->args[i] = new T[this->columns];
		for (size_t i = 0; i < this->rows; i++)
			for (size_t j = 0; j < this->columns; j++)
				this->args[i][j] = m.args[i][j];
			
	}
	Matrix& operator=(const Matrix& m) {
		if (&m == this) {
			return *this;
		}
		for (size_t i = 0; i < this->rows; i++)
			delete[] this->args[i];
		delete[] this->args;
		this->rows = m.rows;
		this->columns = m.columns;
		this->args = new T * [this->rows];
		for (size_t i = 0; i < this->rows; i++)
			this->args[i] = new T[this->columns];
		for (size_t i = 0; i < this->rows; i++)
			for (size_t j = 0; j < this->columns; j++)
				this->args[i][j] = m.args[i][j];
		return *this;
	}
	void set(size_t rowp, size_t columnp, const T& val) {
		if ((rowp - 1 < 0 || rowp - 1 >= this->rows)) {
			std::exception e("This position not found!");
			throw e;
		}
		if ((columnp - 1 < 0 || columnp - 1 >= this->columns)) {
			std::exception e("This position not found!");
			throw e;
		}
		this->args[rowp - 1][columnp - 1] = val;
	}
	
	T& get(size_t rowp, size_t columnp) const {
		if ((rowp - 1 < 0 || rowp - 1 >= this->rows)) {
			std::exception e("This position not found!");
			throw e;
		}
		if ((columnp - 1 < 0 || columnp - 1 >= this->columns)) {
			std::exception e("This position not found!");
			throw e;
		}
		return this->args[rowp - 1][columnp - 1];
	}

	Matrix mul(const Matrix& m) {
		if (this->columns != m.rows) {
			std::exception e("Amount of columns first matrix not equal amount of rows!");
			throw e;
		}
		Matrix <T> mi(this->rows, m.columns);
		for (size_t i = 0; i < this->rows; i++) {
			for (size_t j = 0; j < m.columns; j++) {
				mi.args[i][j] = 0;
				for (size_t k = 0; k < this->columns; k++)
					mi.args[i][j] += this->args[i][k] * m.args[k][j];
			}
		}
		return mi;
	}

	friend std::ostream& operator << (std::ostream& out, const Matrix& m) {
		for (size_t i = 0; i < m.rows; i++) {
			for (size_t j = 0; j < m.columns; j++) {
				std::cout << m.args[i][j] << '\t';
			}
			std::cout << '\n';
		}
		return out;
	}

	friend std::istream& operator >> (std::istream& in, Matrix& m) {
		std::cout << "Fill in the matrix:\n";
		for (size_t i = 0; i < m.rows; i++)
			for (size_t j = 0; j < m.columns; j++) {
				std::cout << "a" << i + 1 << j + 1 << ":";
				std::cin >> m.args[i][j];
			}
		return in;
	}
	

};


#endif

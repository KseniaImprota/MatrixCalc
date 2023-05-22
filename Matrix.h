#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Matrix
{
private:
	int _row, _column;
	double** matrix;

public:
	Matrix() = default;
	Matrix(int row, int column);
	Matrix(const Matrix& other);
	int getCountRow();
	int getCountColumn();
	double& operator()(int i, int j);
	Matrix transposedMatrix();
	Matrix operator+(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator/(const double);       
	double det();
	void set(int i, int j, double value);
	Matrix inverseMatrix();
	void GetMatrix(int row, int col, const Matrix& tmp);
	Matrix CalcComplements();
	int rang() const;
	Matrix exponentiation(int n);
	void printMatrix();
};




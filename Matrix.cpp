#include "Matrix.h"

Matrix::Matrix(int row, int column)
{
	_row = row;
	_column = column;
	matrix = new double* [row];

	for (int i = 0; i < row; i++) {
		matrix[i] = new double[column];
	}
}

Matrix::Matrix(const Matrix& other)
{
	_row = other._row;
	_column = other._column;
	matrix = new double* [_row];
	for (int i = 0; i < _row; i++) {
		matrix[i] = new double[_column];
		for (int j = 0; j < _column; j++) {
			matrix[i][j] = other.matrix[i][j];
		}
	}
}

int Matrix::getCountRow()
{
	return _row;
}

int Matrix::getCountColumn()
{
	return _column;
}

double& Matrix::operator()(int i, int j)
{
	return matrix[i][j];
}

Matrix Matrix::transposedMatrix()
{
	Matrix C(_column, _row);
	for (size_t i = 0; i < _row; i++)
		for (size_t j = 0; j < _column; j++)
			C.matrix[j][i] = matrix[i][j];
	return C;
}

Matrix Matrix::operator+(const Matrix& other)
{
	if(_row != other._row || _column != other._column)
		throw invalid_argument("!error! You cannot do this. Please, try again");

	Matrix result(_row, _column);
	for (size_t i = 0; i < _row; i++)
	{
		for (size_t j = 0; j < _column; j++)
		{
			result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(const Matrix& other)
{
	if (_row != other._row || _column != other._column)
		throw invalid_argument("!error! You cannot do this. Please, try again");

	Matrix result(_row, _column);
	for (size_t i = 0; i < _row; i++)
	{
		for (size_t j = 0; j < _column; j++)
		{
			result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
		}
	}
	return result;
}


Matrix Matrix::operator/(const double divisor) {
	if (divisor == 0) {
		throw std::invalid_argument("Division by zero. You cannot do this. Please, try again ");
	}
	Matrix result(_row,_column);
	for (int i = 0; i < _row; i++) {
		for (int j = 0; j < _column; j++) {
			result.matrix[i][j] = matrix[i][j] / divisor;
		}
	}
	return result;
}

double Matrix::det()
{
	double determinant = 0;
	if (_row == _column) { // определитель существует только для квадратных матриц
		if (_row == 1) {
			determinant = matrix[0][0];
		}
		else if (_row == 2) {
			determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else {
			for (int j = 0; j < _column; ++j) {
				Matrix submatrix(_row - 1, _column - 1);
				for (int i = 1; i < _row; ++i) {
					for (int k = 0; k < _column; ++k) {
						if (k < j) {
							submatrix.set(i - 1, k, matrix[i][k]);
						}
						else if (k > j) {
							submatrix.set(i - 1, k - 1, matrix[i][k]);
						}
					}
				}
				double subdeterminant = submatrix.det();
				determinant += matrix[0][j] * ((j % 2 == 0) ? 1 : -1) * subdeterminant;
			}
		}
	}
	return determinant;
}

void Matrix::set(int i, int j, double value)
{
	{
		matrix[i][j] = value;
	}
}

Matrix Matrix::CalcComplements() {
	if ((this->matrix == nullptr) && (this->_row < 1)) {
		throw length_error("Oh, no! Your matrix is empty");
	}
	if (this->_row != this->_column) {
		throw std::length_error("Error: matrix size is wrong");
	}
	Matrix result(this->_row, this->_column);
	Matrix minor(this->_row - 1, this->_column - 1);
	double determinant = 0.0;
	for (int i = 0; i < this->_row; i++) {
		for (int j = 0; j < this->_column; j++) {
			this->GetMatrix(i, j, minor);
			determinant = minor.det();
			result.matrix[i][j] = pow(-1, i + j) * determinant;
		}
	}
	return result;
}


Matrix Matrix::inverseMatrix()
{
	if ((this->matrix == nullptr) && (this->_row < 1)) {
		throw length_error("Your matrix is empty");
	}
	if (_row != _column) {
		throw length_error("Error: matrix size is wrong");
	}
	int determinant = det();
	if (determinant == 0) {
		throw length_error("!!!Eror!!! Determinant is 0, try again");
	}
	Matrix result(_row, _column);
	if (_row == 1) {
		result.matrix[0][0] = 1.0 / matrix[0][0];
	}
	else {
		Matrix tmp = CalcComplements();
		result = tmp.transposedMatrix();
		result = result / determinant;
	}

	return result;
}

void Matrix::GetMatrix(int row, int col, const Matrix& tmp)
{
	int m_row = 0;
	int m_col = 0;
	for (int i = 0; i < _row; i++) {
		if (i == row) {
			continue;
		}
		m_col = 0;
		for (int j = 0; j < _column; j++) {
			if (j == col) {
				continue;
			}
			tmp.matrix[m_row][m_col] = matrix[i][j];
			m_col++;
		}
		m_row++;
	}
}

int Matrix::rang() const //неправильно считает 
{
	int rank = 0;
	Matrix tmp(*this); 
	for (int i = 0; i < tmp._column && rank < tmp._row; i++) { 
		int j = rank;
		while (j < tmp._row && tmp.matrix[j][i] == 0) {
			j++;
		}
		if (j >= tmp._row) {
			continue;
		}
		if (j != rank) {
			swap(tmp.matrix[j], tmp.matrix[rank]);
		}
		double k = tmp.matrix[rank][i];
		for (int l = 0; l < tmp._column; l++) {
			tmp.matrix[rank][l] /= k;
		}
		for (int l = rank + 1; l < tmp._row; l++) {
			double k = tmp.matrix[l][i];
			for (int m = 0; m < tmp._column; m++) {
				tmp.matrix[l][m] -= k * tmp.matrix[rank][m];
			}
		}
		rank++;
	}
	return rank;
}


Matrix Matrix::operator*(const Matrix& other)
{
	if (_row != other._column || _column != other._row)
		throw invalid_argument("error");

	Matrix result(_row, other._column);

	for (size_t i = 0; i < result._row; i++)
	{
		for (size_t j = 0; j < result._column; j++)
		{
			result.matrix[i][j] = 0;
			for (size_t k = 0; k < _column; k++)
				result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
		}
	}
	return result;
}


Matrix Matrix::exponentiation(int n) 
{
	Matrix result = *this;
	Matrix temp(_row, _column);
	for (int i = 1; i < n; i++) {
		temp = result;
		result = result * (*this);
	}
	return result;
}



void Matrix::printMatrix()
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n";
}



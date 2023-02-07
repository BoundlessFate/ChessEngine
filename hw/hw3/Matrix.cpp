#include "Matrix.h"
#include <iomanip>
#include <math.h>
#include <algorithm>
Matrix::Matrix() {
	numRows = 0;
	numCols = 0;
}
Matrix::Matrix(const Matrix& a) {
	numRows = a.num_rows();
	numCols = a.num_cols();
	data = new double*[numRows];
	for (unsigned int i=0; i<numRows; i++) {
		data[i] = new double[numCols];
		for (unsigned int j=0; j<numCols; j++) {
			data[i][j] = a.data[i][j];
		}
	}
}
Matrix::Matrix(unsigned int row, unsigned int col, double fill) {
	numRows = row;
	numCols = col;
	data = new double*[row];
	if (fill != 0) {
		for (unsigned int i=0; i<row; i++) {
			data[i] = new double[col];
			std::fill_n(data[i], col, fill);
		}
	} else {
		for (unsigned int i=0; i<row; i++) {
			data[i] = new double[col] {};
		}
	}
}
Matrix::~Matrix() {
	if (numRows != 0 && numCols != 0) {
		for (unsigned int i=0; i<numRows; i++) {
			if (data[i] != nullptr) {
				delete[] data[i];
			}
		}
		delete[] data;
	}
}
bool Matrix::operator== (const Matrix& a) {
	if (a.num_rows() != numRows || a.num_cols() != numCols) {
		return false;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentVal = data[i][j];
			double otherVal;
			a.get(i, j, otherVal);
			if (currentVal != otherVal) {
				return false;
			}
		}
	}
	return true;
}
bool Matrix::operator!= (const Matrix& a) {
	if (a.num_rows() != numRows || a.num_cols() != numCols) {
		return true;
	}
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numRows; j++) {
			double currentVal = data[i][j];
			double otherVal;
			a.get(i, j, otherVal);
			if (currentVal != otherVal) {
				return true;
			}
		}
	}
	return false;
}
void Matrix::clear() {
	if (numRows == 0 || numCols == 0) {
		return;
	}
	for (unsigned int i=0; i<numRows; i++) {
		delete[] data[i];
	}
	delete[] data;
	numRows = 0;
	numCols = 0;
	return;
}
bool Matrix::get(unsigned int row, unsigned int col, double& num) const {
	if ((row > numRows) || (col > numCols)) {
		return false;
	}
	num = data[row][col];
	return true;
}
bool Matrix::set(unsigned int row, unsigned int col, double num) {
	if (row > numRows || col > numCols) {
		return false;
	}
	data[row][col] = num;
	return true;
}
void Matrix::multiply_by_coefficient(double coefficient) {
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numCols; j++) {
			data[i][j] = data[i][j] * coefficient;
		}
	}
}
bool Matrix::swap_row(unsigned int numOne, unsigned int numTwo) {
	if ((numOne > numRows) || (numTwo > numCols)) {
		return false;
	}
	double* tempRow = data[numOne];
	data[numOne] = data[numTwo];
	data[numTwo] = tempRow;
	return true;
}
void Matrix::transpose() {
	double** newMatrix = new double*[numCols];
	for (unsigned int i=0; i<numCols; i++) {
		newMatrix[i] = new double[numRows];
		for (unsigned int j=0; j<numRows; j++) {
			newMatrix[i][j] = data[j][i];
		}
	}
	clear();
	data = newMatrix;
}
bool Matrix::add(const Matrix& matrixB) {
	if (numRows != matrixB.num_rows() || numCols != matrixB.num_cols()) {
		return false;
	}
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numCols; j++) {
			double otherValue;
			matrixB.get(i, j, otherValue);
			data[i][j] = data[i][j] + otherValue;
		}
	}
	return true;
}
bool Matrix::subtract(const Matrix& matrixB) {
	if (numRows != matrixB.num_rows() || numCols != matrixB.num_cols()) {
		return false;
	}
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numCols; j++) {
			double otherValue;
			matrixB.get(i, j, otherValue);
			data[i][j] = data[i][j] - otherValue;
		}
	}
	return true;
}
void Matrix::operator= (const Matrix& a) {
	clear();
	if (a.num_rows() != 0 && a.num_cols() != 0) {
		numRows = a.numRows;
		numCols = a.numCols;
		data = new double*[numRows];
		for (unsigned int i=0; i<numRows; i++) {
			data[i] = new double[numCols];
			for (unsigned int j=0; j<numCols; j++) {
				double tempNum;
				a.get(i, j, tempNum);
				data[i][j] = tempNum;
			}
		}
	}
}
double* Matrix::get_row(unsigned int row) {
	double* requestedRow = NULL;
	if (row >= numRows) {
		return requestedRow;
	}
	requestedRow = new double[numRows];
	for (unsigned int i=0; i<numCols; i++) {
		requestedRow[i] = data[row][i];
	}
	return requestedRow;
}
double* Matrix::get_col(unsigned int col) {
	if (!(col < numCols)) {
		double* nullPointer = NULL;
		return nullPointer;
	}
	double* requestedCol = new double[numCols];
	for (unsigned int i=0; i<numRows; i++) {
		requestedCol[i] = data[i][col];
	}
	return requestedCol;
}
Matrix* Matrix::quarter() {
	Matrix* matrixPointer = new Matrix[4];
	if (num_rows() == 0 || num_cols() == 0) {
		for (unsigned int i=0; i<4; i++) {
			matrixPointer[i] = Matrix();
		}
		return matrixPointer;
	}
	unsigned int rowNum = ceil(double(numRows) / 2);
	unsigned int colNum = ceil(double(numCols) / 2);
	for (unsigned int i=0; i<4; i++) {
		matrixPointer[i] = Matrix(rowNum, colNum, 0);
		if (i == 0) {
			for (unsigned int j=0; j<rowNum; j++) {
				for (unsigned int k=0; k<colNum; k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j, k, currentVal);
				}
			}
		} else if (i == 1) {
			for (unsigned int j=0; j<rowNum; j++) {
				for (unsigned int k=int(double(numCols) /2); k<numCols; k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j, k-colNum, currentVal);
				}
			}
		} else if (i == 2) {
			for (unsigned int j=int(double(numRows) /2); j<numRows; j++) {
				for (unsigned int k=0; k<colNum; k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j-int(double(numRows) /2), k, currentVal);
				}
			}
		} else if (i == 3) {
			for (unsigned int j=int(double(numRows) /2); j<numRows; j++) {
				for (unsigned int k=int(double(numCols) /2); k<numCols; k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j-int(double(numRows) /2), k-int(double(numCols) /2), currentVal);
				}
			}
		}	
	}
	return matrixPointer;
}
std::ostream& operator<< (std::ostream& out, const Matrix& m) {
	out << std::endl;
	out << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
	out << "[ ";
	for (unsigned int i=0; i<m.num_rows(); i++) {
		for (unsigned int j=0; j<m.num_cols(); j++) {
			double tempNum;
			m.get(i, j, tempNum);
			out << tempNum;
			if (j < m.num_cols() - 1) {
				out << " ";
			}
		}
		if (i < m.num_rows() - 1) {
			out << std::endl << "  ";
		}
	}
	if (m.num_cols() != 0) {
		out << " ";
	}
	out << "]" << std::endl;
	return out;
}


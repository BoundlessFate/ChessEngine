#include "Matrix.h"
#include <iomanip>
#include <math.h>
Matrix::Matrix() {
	numRows = 0;
	numCols = 0;
}
Matrix::Matrix(const Matrix& a) {
	if (a.num_rows() == 0 || a.num_cols() == 0) {
		numRows = 0;
		numCols = 0;
	} else {
		numRows = a.num_rows();
		numCols = a.num_cols();
		data = new double*[num_rows()];
		for (unsigned int i=0; i<num_rows(); i++) {
			data[i] = new double[num_cols()];
			for (unsigned int j=0; j<num_cols(); j++) {
				double tempNum;
				a.get(i, j, tempNum);
				set(i, j, tempNum);
			}
		}
	}
}
Matrix::Matrix(unsigned int row, unsigned int col, double fill) {
	if (row == 0 || col == 0) {
		numRows = 0;
		numCols = 0;
	} else {
		numRows = row;
		numCols = col;
		data = new double*[num_rows()];
		for (unsigned int i=0; i<num_rows(); i++) {
			data[i] = new double[num_cols()];
			for (unsigned int j=0; j<num_cols(); j++) {
				set(i, j, fill);
			}
		}
	}
}
bool Matrix::operator== (const Matrix& a) {
	if (a.num_rows() != num_rows() || a.num_cols() != num_cols()) {
		return false;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentVal;
			double otherVal;
			get(i, j, currentVal);
			a.get(i, j, otherVal);
			if (currentVal != otherVal) {
				return false;
			}
		}
	}
	return true;
}
bool Matrix::operator!= (const Matrix& a) {
	if (a.num_rows() != num_rows() || a.num_cols() != num_cols()) {
		return true;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentVal;
			double otherVal;
			get(i, j, currentVal);
			a.get(i, j, otherVal);
			if (currentVal != otherVal) {
				return true;
			}
		}
	}
	return false;
}
void Matrix::clear() {
	if (num_rows() == 0 || num_cols() == 0) {
		return;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		delete[] data[i];
	}
	delete[] data;
	numRows = 0;
	numCols = 0;
	return;
}
bool Matrix::get(unsigned int row, unsigned int col, double& num) const {
	if (!(row < num_rows() && col < num_cols())) {
		return false;
	}
	num = data[row][col];
	return true;
}
bool Matrix::set(unsigned int row, unsigned int col, double num) {
	if (!(row < num_rows() && col < num_cols())) {
		return false;
	}
	data[row][col] = num;
	return true;
}
void Matrix::multiply_by_coefficient(double coefficient) {
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentVal;
			get(i, j, currentVal);
			set(i, j, currentVal * coefficient);
		}
	}
}
bool Matrix::swap_row(unsigned int numOne, unsigned int numTwo) {
	if (!(numOne < num_rows() && numTwo < num_cols())) {
		return false;
	}
	double* tempRow = data[numOne];
	data[numOne] = data[numTwo];
	data[numTwo] = tempRow;
	return true;
}
void Matrix::transpose() {
	double** newMatrix = new double*[num_cols()];
	for (unsigned int i=0; i<num_cols(); i++) {
		newMatrix[i] = new double[num_rows()];
		for (unsigned int j=0; j<num_rows(); j++) {
			double tempNum;
			get(j, i, tempNum);
			newMatrix[i][j] = tempNum;
		}
	}
	clear();
	data = newMatrix;
}
bool Matrix::add(const Matrix& matrixB) {
	if (num_rows() != matrixB.num_rows() || num_cols() != matrixB.num_cols()) {
		return false;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentValue;
			double otherValue;
			get(i, j, currentValue);
			matrixB.get(i, j, otherValue);
			set(i, j, currentValue + otherValue);
		}
	}
	return true;
}
bool Matrix::subtract(const Matrix& matrixB) {
	if (num_rows() != matrixB.num_rows() || num_cols() != matrixB.num_cols()) {
		return false;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentValue;
			double otherValue;
			get(i, j, currentValue);
			matrixB.get(i, j, otherValue);
			set(i, j, currentValue - otherValue);
		}
	}
	return true;
}
void Matrix::operator= (const Matrix& a) {
	clear();
	if (a.num_rows() == 0 || a.num_cols() == 0) {
		numRows = 0;
		numCols = 0;
	} else {
		numRows = a.num_rows();
		numCols = a.num_cols();
		data = new double*[num_rows()];
		for (unsigned int i=0; i<num_rows(); i++) {
			data[i] = new double[num_cols()];
			for (unsigned int j=0; j<num_cols(); j++) {
				double tempNum;
				a.get(i, j, tempNum);
				set(i, j, tempNum);
			}
		}
	}
}
double* Matrix::get_row(unsigned int row) {
	double* requestedRow = NULL;
	if (!(row < num_rows())) {
		return requestedRow;
	}
	requestedRow = data[row];
	return requestedRow;
}
double* Matrix::get_col(unsigned int col) {
	if (!(col < num_cols())) {
		double* nullPointer = NULL;
		return nullPointer;
	}
	double colArray[num_cols()];
	double* requestedCol = colArray;
	for (unsigned int i=0; i<num_rows(); i++) {
		double tempVal;
		get(i, col, tempVal);
		requestedCol[i] = tempVal;
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
	unsigned int rowNum = ceil(double(num_rows()) / 2);
	unsigned int colNum = ceil(double(num_cols()) / 2);
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
				for (unsigned int k=int(double(num_cols()) /2); k<num_cols(); k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j, k-colNum, currentVal);
				}
			}
		} else if (i == 2) {
			for (unsigned int j=int(double(num_rows()) /2); j<num_rows(); j++) {
				for (unsigned int k=0; k<colNum; k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j-int(double(num_rows()) /2), k, currentVal);
				}
			}
		} else if (i == 3) {
			for (unsigned int j=int(double(num_rows()) /2); j<num_rows(); j++) {
				for (unsigned int k=int(double(num_cols()) /2); k<num_cols(); k++) {
					double currentVal;
					get(j, k, currentVal);
					matrixPointer[i].set(j-int(double(num_rows()) /2), k-int(double(num_cols()) /2), currentVal);
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
			out << std::endl;
		}
	}
	if (m.num_cols() != 0) {
		out << " ";
	}
	out << "]" << std::endl;
	return out;
}


// Include .h file
#include "Matrix.h"
// math.h for ceil function 
#include <math.h>
// Default Constructor, sets numRows and numCols to 0
Matrix::Matrix() {
	numRows = 0;
	numCols = 0;
}
// Copy Constructor - Copys other matrix
Matrix::Matrix(const Matrix& a) {
	// Set numRows and numCols
	numRows = a.num_rows();
	numCols = a.num_cols();
	// Copy the data to this matrix
	data = new double*[numRows];
	for (unsigned int i=0; i<numRows; i++) {
		data[i] = new double[numCols];
		for (unsigned int j=0; j<numCols; j++) {
			data[i][j] = a.data[i][j];
		}
	}
}
// Fill Constructor - fills the matrix with a fill value
Matrix::Matrix(unsigned int row, unsigned int col, double fill) {
	// Set numRows and numCols
	numRows = row;
	numCols = col;
	// Fill data with values
	data = new double*[row];
	// Normal fill
	if (fill != 0) {
		for (unsigned int i=0; i<row; i++) {
			data[i] = new double[col];
			// fill_n fills the array with the fill value
			std::fill_n(data[i], col, fill);
		}
		// If fill=0, this function can slightly optimize runtime
	} else {
		for (unsigned int i=0; i<row; i++) {
			data[i] = new double[col] {};
		}
	}
}
// Deconstructor
Matrix::~Matrix() {
	if (numRows != 0 && numCols != 0) {
		for (unsigned int i=0; i<numRows; i++) {
			if (data[i] != nullptr) {
				// Delete rows
				delete[] data[i];
			}
		}
		// Delete the array of pointers
		delete[] data;
	}
}
// == Operator Overload
bool Matrix::operator== (const Matrix& a) {
	// Check if the number of rows and columns match
	if (a.num_rows() != numRows || a.num_cols() != numCols) {
		return false;
	}
	for (unsigned int i=0; i<num_rows(); i++) {
		for (unsigned int j=0; j<num_cols(); j++) {
			double currentVal = data[i][j];
			double otherVal;
			a.get(i, j, otherVal);
			// If any values are different, return false
			if (currentVal != otherVal) {
				return false;
			}
		}
	}
	// If nothing is different, return true
	return true;
}
// != Operator Overload
bool Matrix::operator!= (const Matrix& a) {
	// Check if the number of rows and columns dont match
	if (a.num_rows() != numRows || a.num_cols() != numCols) {
		return true;
	}
	for (unsigned int i=0; i<numRows; i++) {
	// Set temporary numRows and numCols
		for (unsigned int j=0; j<numRows; j++) {
			double currentVal = data[i][j];
			double otherVal;
			a.get(i, j, otherVal);
			// If any values are different, return true
			if (currentVal != otherVal) {
				return true;
			}
		}
	}
	// If both matrices are identical, return false
	return false;
}
// Clear deletes all heap data for the matrix
void Matrix::clear() {
	if (numRows == 0 || numCols == 0) {
		return;
	}
	for (unsigned int i=0; i<numRows; i++) {
		// Delete The Rows
		delete[] data[i];
	}
	// Delete the column of pointers
	delete[] data;
	// Set numRows and numCols to 0
	numRows = 0;
	numCols = 0;
	return;
}
// Get a value at an index and pass it into the num parameter
bool Matrix::get(unsigned int row, unsigned int col, double& num) const {
	if ((row > numRows) || (col > numCols)) {
		std::cerr << "Error 1: Index Out Of Bounds" << std::endl;
		return false;
	}
	// If the row and col are valid indexes, set num = the value at the index
	num = data[row][col];
	return true;
}
// Set a vakue at an index with the num parameter
bool Matrix::set(unsigned int row, unsigned int col, double num) {
	if (row > numRows || col > numCols) {
		return false;
	}
	// If the row and col are valid indexes, set the index equal to num
	data[row][col] = num;
	return true;
}
// Multiplies every value by the parameter
void Matrix::multiply_by_coefficient(double coefficient) {
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numCols; j++) {
			// Multiply each index by coefficient
			data[i][j] = data[i][j] * coefficient;
		}
	}
}
// Swap two rows in the matrix
bool Matrix::swap_row(unsigned int numOne, unsigned int numTwo) {
	// Check that the numOne and numTwo values fit in the matrix
	if ((numOne > numRows) || (numTwo > numCols)) {
		std::cerr << "Error 2: Row Index Out Of Bounds" << std::endl;
		return false;
	}
	// Create a local pointer array temporarily, and set it equal to the first row
	double* tempRow = data[numOne];
	// Set the pointer for the first row to the pointer for the second
	data[numOne] = data[numTwo];
	// Set The pointer for the second row to the temporary pointer array
	data[numTwo] = tempRow;
	return true;
}
// Transpose the matrix
void Matrix::transpose() {
	// Create a new matrix
	double** newMatrix = new double*[numCols];
	// Loop through columns in the original matrix
	for (unsigned int i=0; i<numCols; i++) {
		newMatrix[i] = new double[numRows];
		// Loop through rows in the original matrix
		for (unsigned int j=0; j<numRows; j++) {
			// Set [row][column] for the new matrix to [column][row] of the old one 
			newMatrix[i][j] = data[j][i];
		}
	}
	// Clear the data from the heap for the original matrix
	clear();
	// Set data to the new matrix
	data = newMatrix;
}
// Adds two matrices together
bool Matrix::add(const Matrix& matrixB) {
	if (numRows != matrixB.num_rows() || numCols != matrixB.num_cols()) {
		std::cerr << "Error 3: Matrices Are Not The Same Size" << std::endl;
		return false;
	}
	// If the matrices are the same size, run the rest of the code
	// Loop through all values
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numCols; j++) {
			double otherValue;
			matrixB.get(i, j, otherValue);
			// Add the two values together at a specific row and column
			data[i][j] = data[i][j] + otherValue;
		}
	}
	return true;
}
// Subtracts two matrices
bool Matrix::subtract(const Matrix& matrixB) {
	if (numRows != matrixB.num_rows() || numCols != matrixB.num_cols()) {
		std::cerr << "Error 4: Matrices Are Not The Same Size" << std::endl;
		return false;
	}
	// Only run the following code if the matrices are the same size
	// Loop through all values
	for (unsigned int i=0; i<numRows; i++) {
		for (unsigned int j=0; j<numCols; j++) {
			double otherValue;
			matrixB.get(i, j, otherValue);
			// Subtract one value at an index from the value of the other matrix
			data[i][j] = data[i][j] - otherValue;
		}
	}
	return true;
}
// = Operator Overload
void Matrix::operator= (const Matrix& a) {
	// Free the memory in the heap
	clear();
	// If the matrix a isn't a blank matrix...
	if (a.num_rows() != 0 && a.num_cols() != 0) {
		// Set numRows and numCols
		numRows = a.numRows;
		numCols = a.numCols;
		// Create a new matrix
		data = new double*[numRows];
		for (unsigned int i=0; i<numRows; i++) {
			data[i] = new double[numCols];
			for (unsigned int j=0; j<numCols; j++) {
				double tempNum;
				a.get(i, j, tempNum);
				// Copy over each value to the new matrix
				data[i][j] = tempNum;
			}
		}
	}
}
// Returns a pointer to a specific row
double* Matrix::get_row(unsigned int row) {
	double* requestedRow = NULL;
	// Return null pointer if the specified row is out of bounds
	if (row >= numRows) {
		std::cerr << "Error 5: Row Index Is Out Of Bounds" << std::endl;
		return requestedRow;
	}
	// Create a new array in the heap
	requestedRow = new double[numRows];
	for (unsigned int i=0; i<numCols; i++) {
		// Set the values of the array equal to the values of the specified row
		requestedRow[i] = data[row][i];
	}
	return requestedRow;
}
// Returns a pointer to a specific column
double* Matrix::get_col(unsigned int col) {
	// Returns null if the column is out of bunds
	if (!(col < numCols)) {
		std::cerr << "Error 6: Column Index Is Out Of Bounds" << std::endl;
		double* nullPointer = NULL;
		return nullPointer;
	}
	// Create a matrix in the heap
	double* requestedCol = new double[numCols];
	for (unsigned int i=0; i<numRows; i++) {
		// set the values of the array to the row index and column of the matrix
		requestedCol[i] = data[i][col];
	}
	return requestedCol;
}
// Returns 4 matrices, each being a quarter of the original matrix
Matrix* Matrix::quarter() {
	// Create an array of matrices
	Matrix* matrixPointer = new Matrix[4];
	// If the matrix doesnt have anything in it, return 4 empty matrices
	if (num_rows() == 0 || num_cols() == 0) {
		for (unsigned int i=0; i<4; i++) {
			matrixPointer[i] = Matrix();
		}
		return matrixPointer;
	}
	// Set rowNum and colNum for each of the matrices
	unsigned int rowNum = ceil(double(numRows) / 2);
	unsigned int colNum = ceil(double(numCols) / 2);
	// Loop through the array
	for (unsigned int i=0; i<4; i++) {
		// Create the matrices
		matrixPointer[i] = Matrix(rowNum, colNum, 0);
		// Each one of the 4 loop do very similar stuff, but access different values
		// i==0 is TL, i==1 is TR, i==2 is BL, i==3 is BR
		// Loops through rowNum and colNum to set values of the matrices
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
					unsigned int indexRow = j-int(double(numRows)/2);
					unsigned int indexCol = k-int(double(numCols)/2);
					matrixPointer[i].set(indexRow, indexCol, currentVal);
				}
			}
		}	
	}
	return matrixPointer;
}
void Matrix::resize(unsigned int row, unsigned int col, double fill) {
	// FIRST THE FILL VALUE IS PLACED ON ALL INDEXES
	// Fill data with values
	double** tempData = new double*[row];
	// Normal fill
	for (unsigned int i=0; i<row; i++) {
		tempData[i] = new double[col];
		// fill_n fills the array with the fill value
		std::fill_n(tempData[i], col, fill);
	}
	// NEXT THE ORIGINAL VALUES ARE COPIED OVER
	for (unsigned int i=0; i<row && i<numRows; i++) {
		for (unsigned int j=0; j<col && j<numCols; j++) {
			tempData[i][j] = data[i][j];
		}
	}
	// Clear Original Data From Heap
	clear();
	// Set Actual Matrix's Data To The New Data
	data = tempData;
	numRows = row;
	numCols = col;
}
// << Operator Overload For Outputting
std::ostream& operator<< (std::ostream& out, const Matrix& m) {
	out << std::endl;
	// For the Matrix Size
	out << m.num_rows() << " x " << m.num_cols() << " matrix:" << std::endl;
	out << "[ ";
	// Output the values at each index
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
			// Add a space if the index isnt at the end of a row
			out << std::endl << "  ";
		}
	}
	if (m.num_cols() != 0) {
		// Formats the left side properly for the matrix
		out << " ";
	}
	out << "]" << std::endl;
	return out;
}


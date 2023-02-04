#include <iostream>
class Matrix {
public:
	Matrix();
	Matrix(const Matrix& a);
	Matrix(unsigned int row, unsigned int col, double fill);
	~Matrix();
	bool operator== (const Matrix& a);
	bool operator!= (const Matrix& a);
	void operator= (const Matrix& a);
	unsigned int num_rows() const {return numRows;}
	unsigned int num_cols() const {return numCols;}
	void clear();
	bool get(unsigned int row, unsigned int col, double& num) const;
	bool set(unsigned int row, unsigned int col, double num);
	void multiply_by_coefficient(double coefficient);
	bool swap_row(unsigned int numOne, unsigned int numTwo);
	void transpose();
	bool add(const Matrix& matrixB);
	bool subtract(const Matrix& matrixB);
	double* get_row(unsigned int row);
	double* get_col(unsigned int col);
	Matrix* quarter();
private:
	unsigned int numRows;
	unsigned int numCols;
	double** data;
};
std::ostream& operator<< (std::ostream& out, const Matrix& m);

#include <iostream>
class Matrix {
public:
	// Constructors
	// Default Constructor
	Matrix();
	// Copy Other Matrix Constructor
	Matrix(const Matrix& a);
	// Fill Constructor
	Matrix(unsigned int row, unsigned int col, double fill);
	// Destruuuctor
	~Matrix();
	// Operator Overloads
	// == Overload
	bool operator== (const Matrix& a);
	// != Overload
	bool operator!= (const Matrix& a);
	// = Overload
	void operator= (const Matrix& a);
	// Accessors
	// Returns Number Of Rows
	unsigned int num_rows() const {return numRows;}
	// Returns Number Of Columns
	unsigned int num_cols() const {return numCols;}
	// Other Functions
	// Clears Data From The Heap
	void clear();
	// Returns True Or False And Sets Num Equal To the Value At That Index
	bool get(unsigned int row, unsigned int col, double& num) const;
	// Returns True Or False And Sets Data Equal To Num At The Specified Index
	bool set(unsigned int row, unsigned int col, double num);
	// Multiplies The Entire Matrix By The Input
	void multiply_by_coefficient(double coefficient);
	// Swaps Two Rows In The Matrix
	bool swap_row(unsigned int numOne, unsigned int numTwo);
	// Transposes The Matrix
	void transpose();
	// Adds Two Matrices Together If They Are The Same Size
	bool add(const Matrix& matrixB);
	// Subtracts Two Matrices If They Are The Same Size
	bool subtract(const Matrix& matrixB);
	// Returns A Pointer To A Specified Row
	double* get_row(unsigned int row);
	// Returns A Pointer To A Specified Column
	double* get_col(unsigned int col);
	// Returns An Array Of Matrices, Each Being A Matrix Of One Quarter Of The Original Matrix
	Matrix* quarter();
	// Resizes the matrix and fills in any values with the fill value if it is larger
	void resize(unsigned int row, unsigned int col, double fill);
private:
	// Private Variables
	// Number Of Rows
	unsigned int numRows;
	// Number Of Columns
	unsigned int numCols;
	// The Matrix Itself
	double** data;
};
// Operator Overload
// Overloads The << Operator For Outputting
std::ostream& operator<< (std::ostream& out, const Matrix& m);

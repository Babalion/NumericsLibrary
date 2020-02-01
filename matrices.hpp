#pragma once

#include <iostream>
#include <math.h>


//this header file provides some stuff for calculations with matrices


template<typename mEnt> //datatype of matrix-entries
class DynamicMatrix {
private:
	mEnt** data;
	unsigned int rows;
	unsigned int columns;
public:
	//------CONSTRUCTORS------------------------------------------------------
	DynamicMatrix(); //standard constructor
	DynamicMatrix(unsigned int rows,unsigned int columns); //individual dimension constructor
	DynamicMatrix(const DynamicMatrix<mEnt> &other);//Copy Constructor
	//DynamicMatrix(DynamicMatrix &&other); //Move Constructor
	~DynamicMatrix(); //destructor

	//-------METHODS---------------------------------
	int getRows() const;
	int getColumns() const;
	mEnt get(unsigned int rows,unsigned int columns) const;
	void set(unsigned int rows,unsigned int columns, mEnt value);
	void plotMatrix();
	void initMatrix();
	bool isUpperTriangular();


	//-------OPERATOR-OVERLOADING----------------
	mEnt& operator()(unsigned int rows,unsigned int columns);
	DynamicMatrix<mEnt> operator+(const DynamicMatrix<mEnt> &other);
	DynamicMatrix<mEnt> operator-(const DynamicMatrix<mEnt> &other);
	DynamicMatrix<mEnt> operator*(const DynamicMatrix<mEnt> &other);
	DynamicMatrix<mEnt>& operator=(const DynamicMatrix<mEnt> &other);
};

/////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
//--------------------------OTHER FUNCTIONS--------------------------------------
//-------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////

template<typename mEnt>
DynamicMatrix<mEnt> solve(DynamicMatrix<mEnt> mat, DynamicMatrix<mEnt> vec);

template<typename mEnt>
int ref(DynamicMatrix<mEnt> &mat, DynamicMatrix<mEnt> &vec);

template<typename mEnt>
DynamicMatrix<mEnt> switchRow(DynamicMatrix<mEnt> mat, unsigned int i, unsigned int j);

template<typename mEnt>
DynamicMatrix<mEnt> solveTriDiag(DynamicMatrix<mEnt> mat, DynamicMatrix<mEnt> vec);





//######################################################################################################
//######################################################################################################
/////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
//---------------------------Class DynamicMatrix---------------------------------
//-------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////


//-----------------------------------------------------------------
//CONSTRUCTORS AND DESTRUCTORS
//-----------------------------------------------------------------

//standard constructor 3x3 Matrix
template<typename mEnt>
DynamicMatrix<mEnt>::DynamicMatrix() {
	rows = 3;
	columns = 3;
	data = new mEnt*[rows];
	for (int i = 0; i < rows; ++i)
		data[i] = new mEnt[columns];

	//initialize with 1,2,3...
	mEnt k = static_cast<mEnt>(1);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			data[i][j] = k;
			k++;
		}
	}
}

//individual dimension constructor
template<typename mEnt>
DynamicMatrix<mEnt>::DynamicMatrix(unsigned int _rows, unsigned int _columns) {
	rows = _rows;
	columns = _columns;
	data = new mEnt*[rows];
	for (int i = 0; i < rows; ++i)
		data[i] = new mEnt[columns];

	//init all with 0
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			data[i][j] = 0;
		}
	}
}

//Copy constructor
template<typename mEnt>
DynamicMatrix<mEnt>::DynamicMatrix(const DynamicMatrix<mEnt> &other) {
	rows = other.rows;
	columns = other.columns;
	data = new mEnt*[rows];
	for (int i = 0; i < rows; ++i) {
		data[i] = new mEnt[columns];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
		{
			data[i][j] = other.data[i][j];
		}
	}
}

//destructor
template<typename mEnt>
DynamicMatrix<mEnt>::~DynamicMatrix() {
	//delete each sub-array
	for (int i = 0; i < rows; ++i) {
		delete[] data[i];
	}
	//delete the array of pointers
	delete[] data;
}



//---------------------------------------------------------
//METHODS
//---------------------------------------------------------
template<typename mEnt>
int DynamicMatrix<mEnt>::getRows() const {
	return rows;
}
template<typename mEnt>
int DynamicMatrix<mEnt>::getColumns() const {
	return columns;
}
template<typename mEnt>
mEnt DynamicMatrix<mEnt>::get(unsigned int rows, unsigned int columns) const {
	return data[rows][columns];
}
template<typename mEnt>
void DynamicMatrix<mEnt>::set(unsigned int rows, unsigned int columns, mEnt value) {
	data[rows][columns] = value;
}

//plots the matrix with tabs between columns
template<typename mEnt>
void DynamicMatrix<mEnt>::plotMatrix() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; ++j) {
			std::cout << data[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

//initializes the matrix by userinteraction
template<typename mEnt>
void DynamicMatrix<mEnt>::initMatrix() {
	std::cout << "Enter the asked values to initialize." << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			std::cout << "(" << i << "," << j << "): ";
			std::cin >> data[i][j];
			//std::cout << std::endl;
		}
	}
}

// returns true if all elements under the main diagonal are equal to zero
// else false
template<typename mEnt>
bool DynamicMatrix<mEnt>::isUpperTriangular() {
	if (rows != columns) {
		//Matrix is not quadratic
		std::cout << "Matrix is not quadratic" << std::endl;
		return false;
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (i > j && data[i][j] != 0) {
				std::cout << i << "," << j << std::endl;
				return false;
			}
		}
	}
	return true;
}


//----------------------------------------------------------------
// OPERATOR OVERLOADING
//----------------------------------------------------------------

//simplifies handling matrices
template<typename mEnt>
mEnt& DynamicMatrix<mEnt>::operator()(unsigned int rows,unsigned int columns) {
	return data[rows][columns];
}

// Standard matrix addition elementwise
// Programm throws an error, if dimension doesn't match
template<typename mEnt>
DynamicMatrix<mEnt> DynamicMatrix<mEnt>::operator+(const DynamicMatrix<mEnt> &other) {
	if (rows != other.rows || columns != other.columns) {
		std::cerr << "ERROR: Dimension Missmatch!" << std::endl;
	}

	DynamicMatrix<mEnt> retMat(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			retMat(i, j) = data[i][j] + other.data[i][j];
		}
	}
	return retMat;
}

// Standard matrix subtraction elementwise
// Programm throws an error, if dimension doesn't match
template<typename mEnt>
DynamicMatrix<mEnt> DynamicMatrix<mEnt>::operator-(const DynamicMatrix &other) {
	if (rows != other.rows || columns != other.columns) {
		std::cerr << "ERROR: Dimension Missmatch!" << std::endl;
	}

	DynamicMatrix<mEnt> retMat(rows, columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			retMat(i, j) = data[i][j] - other.data[i][j];
		}
	}
	return retMat;
}

// Standard matrix multiplication
// Programm throws an error, if dimension doesn't match
template<typename mEnt>
DynamicMatrix<mEnt> DynamicMatrix<mEnt>::operator*(const DynamicMatrix &other) {
	if (columns != other.rows) {
		std::cerr << "ERROR: Dimension Missmatch!" << std::endl;
		exit(11);
	}

	DynamicMatrix<mEnt> retMat(rows, other.columns);
	mEnt temp = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < other.columns; j++)
		{
			for (int k = 0; k < columns; k++) {
				temp += data[i][k] * other.data[k][j];
			}
			retMat(i, j) = temp;
			temp = 0;
		}
	}
	return retMat;
}

// Operator = to assign a calculated matrix to an other
template<typename mEnt>
DynamicMatrix<mEnt>& DynamicMatrix<mEnt>::operator=(const DynamicMatrix &other) {
	if (rows != other.rows || columns != other.columns) {
		for (int i = 0; i < rows; ++i) {
			delete[] data[i];
		}
		delete[] data;
		rows = other.rows;
		columns = other.columns;
		data = new mEnt*[rows];
		for (int i = 0; i < rows; ++i)
			data[i] = new mEnt[columns];
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
		{
			data[i][j] = other.data[i][j];
		}
	}
	return *this;
}




/////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------
//--------------------------OTHER FUNCTIONS--------------------------------------
//-------------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////

// Solves the Equation mat * X = vec
// returns X as a n-x-1 Matrix
// if Dimension missmatches, Programm will stop
template<typename mEnt>
DynamicMatrix<mEnt> solve(DynamicMatrix<mEnt> mat, DynamicMatrix<mEnt> vec) {
	if (mat.isUpperTriangular() == 0 || vec.getRows() != mat.getColumns() || vec.getColumns() != 1) {
		std::cerr << "ERROR: Dimension Missmatch!" << std::endl;
		exit(12);
	}

	DynamicMatrix<mEnt> X(mat.getRows(), 1);
	mEnt temp = 0;
	for (int i = mat.getRows() - 1; i >= 0; i = i - 1) {
		for (int j = i + 1; j < mat.getRows(); ++j) {
			temp += mat(i, j)*X(j, 0);
		}
		X(i, 0) = (vec(i, 0) - temp) / mat(i, i);// /mat(i,i) not necessary if all diagonal elements are equal 1
		temp = 0;
	}
	return X;
}


// returns a gaussian elimination form of the Matrix call by value
// and of the Solution vector call by value
// returns the values themselves, if the matrix is not quadratic
// pivioting, if def PIVIOTING
#define PIVIOTING
// Matrix has to be full rank <==> det(mat)!=0
template<typename mEnt>
int ref(DynamicMatrix<mEnt> &mat, DynamicMatrix<mEnt> &vec) {
	if (mat.getRows() != mat.getColumns() || vec.getRows() != mat.getColumns() || vec.getColumns() != 1) {
		return 1;
	}

	DynamicMatrix<mEnt> mat_old(mat); //constant initial Matrix for one iteration
	int size = mat.getRows();
	for (int i = 0; i < size; i++)
	{
#ifdef PIVIOTING
		//if mat_old(i,i)==0
		//calculate the row to change with
		if (mat_old(i, i) == 0) {
			int iterate = i + 1;
			bool foundRow = false;

			while (iterate < size && foundRow == false) {
				if (mat_old(iterate, i) != 0) {
					// found row 'iterate' with no 0 in front of
					mat = switchRow(mat, i, iterate);
					mat_old = switchRow(mat_old, i, iterate);
					vec = switchRow(vec, i, iterate);
					foundRow = true;
				}
				iterate++;
			}
			//when no nonzero line was found,
			//take the one with the biggest diagonal element
			mEnt temp = 0;
			int biggest = 0;
			if (foundRow == false) {
				for (int j = i; j < size; j++) {
					if (mat(j, j) > temp) {
						temp = mat(j, j);
						biggest = j;
					}
				}
				mat = switchRow(mat, biggest, i);
				mat_old = switchRow(mat_old, biggest, i);
				vec = switchRow(vec, biggest, i);
			}

		}


#endif // PIVIOTING

		for (int k = i; k < size; k++)//Divide row i by the diagonal element mii
		{
			mat(i, k) = mat(i, k) / mat_old(i, i);
		}
		vec(i, 0) = vec(i, 0) / mat_old(i, i);//	Divide b[i] by the diagonal element mii

		for (int j = i + 1; j < size; j++)
		{
			mat_old = mat;
			for (int k = i; k < size; k++)
			{
				mat(j, k) = mat(j, k) - mat_old(i, k) * mat_old(j, i); //Subtract(row i) * mji from row j
			}
			vec(j, 0) = vec(j, 0) - mat_old(j, i)*vec(i, 0);//Subtract b[i]  m(j; i) from b[j]
			mat_old = mat;
		}
	}
	return 0; //successfull


	//-------------------------------------------
	//PSEUDOCODE for ref() without pivioting
	/*for i = 0 to size - 1 do
	Divide row i by the diagonal element mii
	Divide b[i] by the diagonal element mii
	for j = i + 1 to size - 1 do
		Subtract(row i) * mji from row j
		Subtract b[i]  m(j; i) from b[j]
	end for
	end for*/
	//-------------------------------------------
}


//switches the i-th and j-th row of a�given matrix
//returns the solution
template<typename mEnt>
DynamicMatrix<mEnt> switchRow(DynamicMatrix<mEnt> mat, int i, int j) {
	if (j == i) {
		return mat;
	}
	DynamicMatrix<mEnt> temp(mat);
	for (int k = 0; k < mat.getColumns(); k++)
	{
		mat(j, k) = temp(i, k);
		mat(i, k) = temp(j, k);
	}

	return mat;
}


//solves the TridiagSystem
//returns the SolutionVector
//works with thomas algorithm
template<typename mEnt>
DynamicMatrix<mEnt> solveTriDiag(DynamicMatrix<mEnt> mat, DynamicMatrix<mEnt> vec) {
	auto a = [&](int i) { return mat(i - 1, i - 2); };
	auto b = [&](int i) { return mat(i - 1, i - 1); };
	auto c = [&](int i) { return mat(i - 1, i); };
	auto d = [&](int i) { return mat(i - 1, 0); };

	if (mat.getColumns() != mat.getRows() || mat.getRows() != vec.getRows()) {
		std::cerr << "solveTriDiag: Dimension Missmatched!";
		std::cin.get();
		exit(4);
	}
	//a_2=mat(1,0)
	//a_3=mat(2,1)
	//a_i=mat(i-1,i-2)
	//b_1=,at(0,0)
	//b_i=mat(i-1,i-1)
	//c_1=mat(0,1)
	//c_i=mat(i-1,i)
	//d_1=vec(0,0)
	//d_i=vec(i-1,0)
	mat.plotMatrix();
	mat(0, 1) = c(1) / b(1);
	for (int i = 2; i < mat.getRows(); i++)
	{
		mat(i - 1, i) = c(i) / (b(i) - c(i - 1)*a(i));
	}
	vec(0, 0) = d(1) / b(1);
	for (int i = 2; i < mat.getRows(); i++)
	{
		vec(i - 1, 0) = (d(i) - d(i - 1)*a(i)) / (b(i) - c(i - 1)*a(i));
	}
	mat.plotMatrix();
	vec.plotMatrix();
	//backsubstitution
	DynamicMatrix<mEnt> retVal(vec.getRows(), 1);
	retVal(vec.getRows() - 1, 0) = vec(vec.getRows() - 1, 0);
	for (int i = vec.getRows() - 2; i >= 1; i--)
	{
		retVal(i - 1, 0) = d(i) - c(i)*retVal(i, 0);
	}
	return retVal;

	// an upper tridiagonal matrix look like:

	//b_1	c_1	.	.	.	.	0
	//a_2	b_2	c_2	.	.	.	0
	//0	a_3	b_3	c_3	.	.	0
	//.	.	.	.			.
	//.		.	.	.		.
	//.			.	.	.	.
	//0	.	.	.	.a_n	b_n

}
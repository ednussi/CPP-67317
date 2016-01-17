/**
 * @file IntMatrix.h
 * @author  ednussi
 * @version 1.0
 * @date 21 Aug 2015
 * 
 * @brief The implemention file for the IntMatrix class

 * @section LICENSE
 * This program is a free software. You can freely redistribute it.
 *
 * @section DESCRIPTION
 * IntMatrix class is a class representing a 2D matrix of integers
 * all function and override of operators are implemented here 
 * Also supplies tools to work with 2D matrices.
 */

#include <iostream>
#include "IntMatrix.h"
#include <assert.h> 

IntMatrix::IntMatrix() : _rows(0), _columns(0)
{
	_intArray = {};
}

void IntMatrix::_createEmptyMatrix(int rows, int columns)
{
	_intArray = new int*[rows]();
	assert(_intArray != nullptr);
	for (int rowsIndex = 0; rowsIndex < rows; rowsIndex++)
	{
		_intArray[rowsIndex] = new int[columns]();
		assert(_intArray != nullptr);
	}
}

void IntMatrix::_deleteMatrix()
{
	if (_intArray != nullptr)
	{
		for (int index = 0; index < _rows; index++)
		{
			delete[] _intArray[index];
			_intArray[index] = nullptr;
		}
	}
	
	delete[] _intArray;
	_intArray = nullptr;

}

void IntMatrix::_initializeMatrix(int maxRows, int maxColumns, const int **newMatrix) const
{
	for (int row = 0; row < maxRows; row++)
	{
		for (int col = 0; col < maxColumns; col++)
		{
			this->_intArray[row][col] = newMatrix[col][row];
		}
	}
}

void IntMatrix::_initializeMatrix(const int **newMatrix) const
{
	this->_initializeMatrix(this->_rows, this->_columns, newMatrix);
}

IntMatrix::IntMatrix(int rows, int columns) : _rows(rows), _columns(columns)
{
	this->_createEmptyMatrix(this->_rows, this->_columns);
}

IntMatrix::IntMatrix(int rows, int columns, const int** data) : IntMatrix(rows, columns)
{
	for (int row = 0; row < this->_rows; row++)
	{
		for (int col = 0; col < this->_columns; col++)
		{
			this->_intArray[row][col] = data[row][col];
		}
	}
}

IntMatrix::IntMatrix(const IntMatrix &matrixToCopy) : \
					 IntMatrix(matrixToCopy._rows, matrixToCopy._columns, 
					 		   (const int**) matrixToCopy._intArray)
{

}

IntMatrix::~IntMatrix()
{
	this->_deleteMatrix();
}

bool IntMatrix::isSameDimensions(const IntMatrix &second) const
{
	return !(this->_rows != second.getRows() ||
			 this->_columns != second.getColumns());

}

bool IntMatrix::isMultipliable(const IntMatrix &rightMatrix) const
{
	return !(this->getColumns() != rightMatrix.getRows());
}

bool IntMatrix::isSquared() const
{
	return !(this->_rows != this->_columns);
}

void IntMatrix::_innerDataAssertCheck(const IntMatrix& matrix) const
{
	assert (matrix._intArray != nullptr);
	for (int row = 0; row < matrix._rows; row++)
	{
		assert(matrix._intArray[row] != nullptr);
	}
}

void IntMatrix::_logicalDimensions(const IntMatrix& matrix) const
{
	assert(!(matrix._rows == 0 && matrix._columns != 0) 
		   && !(matrix._rows != 0 && matrix._columns == 0));

}

void IntMatrix::_runAssertCheck(const IntMatrix& matrix) const
{
	_innerDataAssertCheck(matrix);
	_logicalDimensions(matrix);
}

//______________Assignment operator______________
IntMatrix& IntMatrix::operator=(const IntMatrix& other)
{

	//In case are the same
	if (this == &other)
	{
		return *this;
	}

	_runAssertCheck(other);
	
	//In case aren't of same dimensions
	if (other._rows != this->_rows || other._columns != this->_columns) //TODO isSame
	{
		//delete old and create & initialize the new data
		this->_deleteMatrix();
		this->_rows = other._rows;
		this->_columns = other._columns;
		this->_createEmptyMatrix(other._rows, other._columns);
	}

	//initialize intArray cells
	this->_initializeMatrix((const int**) other._intArray);

	return *this;
}

// ______________Compound assignment operators______________
IntMatrix& IntMatrix::operator+=(const IntMatrix& other)
{
	_runAssertCheck(other);
	assert(this->isSameDimensions(other));

	for (int row = 0; row < other._rows; row++)
	{
		for (int col = 0; col < other._columns; col++)
		{

			this->_intArray[row][col] += other._intArray[row][col];
		}
	}
	return *this;
}

IntMatrix& IntMatrix::operator-=(const IntMatrix& other)
{
	_runAssertCheck(other);
	assert(this->isSameDimensions(other));

	for (int row = 0; row < other._rows; row++)
	{
		for (int col = 0; col < other._columns; col++)
		{
			this->_intArray[row][col] -= other._intArray[row][col];
		}
	}
	return *this;
}

IntMatrix& IntMatrix::operator*=(const IntMatrix& other)
{
	_runAssertCheck(other);
	assert(this->isMultipliable(other));
	IntMatrix temp(*this); 
	this->_columns = other._columns;

	//delete old intArray and intialize new
	this->_deleteMatrix();
	this->_createEmptyMatrix(temp._rows, other._columns);

	//update values
	int multCellSum;
	for (int row = 0; row < this->_rows; row++)
	{
		for (int col = 0; col <this->_columns; col++)
		{
			multCellSum = 0;
			for (int intersec = 0; intersec < other._rows; intersec++)
			{
				multCellSum += temp._intArray[row][intersec] * other._intArray[intersec][col];
			}
			this->_intArray[row][col] = multCellSum;
		}
	}
	return *this;
}

bool IntMatrix::operator==(const IntMatrix& other) const
{
	if (this == &other)
	{
		return true;
	}

	if ((this->_columns == other.getColumns()) || (this->_rows == other.getRows()))
	{
		for (int row = 0; row < this->_rows; row++)
		{
			for (int column = 0; column < this->_columns; column++)
			{
				if (this->_intArray[row][column] != other._intArray[row][column])
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}


bool IntMatrix::operator!=(const IntMatrix& other) const
{
	return !(*this == other);
}


// ____________Binary arithmetic operation______________
IntMatrix& IntMatrix::operator+(const IntMatrix& other) const
{
	return IntMatrix(*this) += other;
}

IntMatrix& IntMatrix::operator-(const IntMatrix& other) const
{
	return IntMatrix(*this) -= other;
}

IntMatrix& IntMatrix::operator*(const IntMatrix& other) const
{
	return IntMatrix(*this) *= other;
}

IntMatrix IntMatrix::trans()
{
	_runAssertCheck(*this);
	IntMatrix transMatrix(this->_columns, this->_rows);
	transMatrix._initializeMatrix((const int**) this->_intArray);
	return transMatrix;
}

int IntMatrix::trace()
{
	_runAssertCheck(*this);
	assert(isSquared());

	int result = 0;
	for (int diagnel = 0; diagnel < this->_rows; diagnel++)
	{
		result += this->_intArray[diagnel][diagnel];
	}
	return result;

}

ostream& operator<<(ostream& os, const IntMatrix& other)
{
	//Asserts for the other recieved Matrix
	assert (other._intArray != nullptr);
	for (int row = 0; row < other._rows; row++)
	{
		assert(other._intArray[row] != nullptr);
	}

	assert(!(other._rows == 0 && other._columns != 0) 
		   && !(other._rows != 0 && other._columns == 0));

	//In case of 0X0 dimension
	if (other._rows == 0 && other._columns == 0)
	{
		os << endl;
		return os;
	}

	for (int row = 0; row < other._rows; row++)
	{
		int col;
		for (col = 0; col < (other._columns - 1); col++)
		{
			os << other._intArray[row][col] << " ";
		}
		os << other._intArray[row][col] << endl;
	}

	return os;
}

int IntMatrix::getRows() const
{
	return this->_rows;
}

int IntMatrix::getColumns() const
{
	return this->_columns;
}
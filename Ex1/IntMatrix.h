/**
 * @file IntMatrix.h
 * @author  ednussi
 * @version 1.0
 * @date 21 Aug 2015
 * 
 * @brief The headear file for the IntMatrix class

 * @section LICENSE
 * This program is a free software. You can freely redistribute it.
 *
 * @section DESCRIPTION
 * IntMatrix class is a class representing a 2D matrix of integers and 
 * tools to work with 2D matrices.
 */

#ifndef _INTMATRIX_H_
#define _INTMATRIX_H_

using namespace std;

/**
* IntMatrix class is a class representing a 2D matrix of integers and 
* tools to work with 2D matrices.
*/
class IntMatrix
{
private:
	//Matrix values
	int **_intArray;
	int _rows, _columns;

	/**
	 * @brief delete all memory allocated and the matrix array data of the matrix
	 */
	void _deleteMatrix();

	/**
	 * @brief creates and allocats memory for the matrix array data of the matrix
	 * @param rows - Matrix rows
	 * @param columns - Matrix columns 
	 */
	void _createEmptyMatrix(int rows, int columns);

	/**
	 * @brief initialize Matrix to wanted newIntMatrix
	 * @param newMatrix - 2D array of int with the data of the matrix
	 */
	void _initializeMatrix(int const **newMatrix) const;

	/**
	 * @brief initialize Matrix to wanted newIntMatrix
	 * @param newMatrix - 2D array of int with the data of the matrix
	 * @param rows - Matrix rows
	 * @param columns - Matrix columns 
	 */
	void _initializeMatrix(int maxRows, int maxColumns, const int **newMatrix) const;

	/**
	 * @brief Check inner data members and assert if they are not initialized
	 * @param other - matrix to check its inner members
	 */
	void _innerDataAssertCheck(const IntMatrix& matrix) const;

	/**
	 * @brief Check if Dimensions are of logical size
	 * @param matrix - matrix to check its size
	 */
	void _logicalDimensions(const IntMatrix& matrix) const;

	/**
	 * @brief Run assert checks on the recieved matrix
	 * @param matrix - matrix to check
	 */
	void _runAssertCheck(const IntMatrix& matrix) const;


public:

	/**
	 * @brief Default Constructor
	 */
	IntMatrix();

	/**
	 * @brief Constructor
	 * @param rows - number of matrix rows
	 * @param columns - number of matrix columns
	 */
	IntMatrix(int rows, int columns);

	/**
	 * @brief Constructor
	 * @param rows - number of matrix rows
	 * @param columns - number of matrix columns
	 * @param data - the Int Array data to be inserted 
	 */
	IntMatrix(int rows, int columns, const int** data);

	/**
	 * @brief Copy Constructor
	 * @param other - An intMatrix to make a copy of
	 */
	IntMatrix(const IntMatrix &matrixToCopy);

	/**
	 * @brief Default destructor
	 */
	~IntMatrix();

	/**
	 * @brief Rows getter
	 * @return The IntMatrix Number of rows
	 */
	int getRows() const;

	/**
	 * @brief Columns getter
	 * @return The IntMatrix Number of coulmns
	 */
	int getColumns() const;

	/**
	 * @brief Override '=' operator for class
	 * @param other - the matrix to assign from
	 * @return IntMatrix with same data memebers as the assign from matrix
	 */
	IntMatrix& operator=(const IntMatrix& other);

	/**
	 * @brief Override '+' operator for class
	 * @param other - the matrix to add it's data members
	 * @return IntMatrix with the summed up data memebers
	 */
	IntMatrix& operator+(const IntMatrix& other) const;

	/**
	 * @brief Override '+=' operator for class
	 * @param other - the matrix to add it's data members
	 * @return the originial IntMatrix with the summed up data memebers
	 */
	IntMatrix& operator+=(const IntMatrix& other);

	/**
	 * @brief Override '-' operator for class
	 * @param other - the matrix to subtract it's data members
	 * @return IntMatrix with the subtracted down data memebers
	 */
	IntMatrix& operator-(const IntMatrix& other) const;

	/**
	 * @brief Override '-=' operator for class
	 * @param other - the matrix to subtract it's data members
	 * @return the original IntMatrix with the subtracted down data memebers
	 */
	IntMatrix& operator-=(const IntMatrix& other);

	/**
	 * @brief Override '*' operator for class
	 * @param other - the matrix to multiply with it's data members
	 * @return IntMatrix with the multiplication product of their data memebers
	 */
	IntMatrix& operator*(const IntMatrix& other) const;

	/**
	 * @brief Override '*=' operator for class
	 * @param other - the matrix to multiply with it's data members
	 * @return the originial IntMatrix with the multiplication product of their data memebers
	 */
	IntMatrix& operator*=(const IntMatrix& other);

	/**
	 * @brief Override '<<' operator for class
	 * @param other - the matrix to print out
	 * @param os - the output stream to enter the data to print to
	 * @return reference to the stream after printing out the matrix
	 */
	friend ostream& operator<<(ostream& os, const IntMatrix& other);

	/**
	* @brief Override '==' operator for class
	* WAS NOT REQUIRED - IS AN ADDITION =]
	* @param other - the matrix to compare to
	* @return True iff matrices are equal
	*/
	bool operator==(const IntMatrix& other) const;
	
	/**
	* @brief Override '!=' operator for class
	* WAS NOT REQUIRED - IS AN ADDITION =]
	* @param other - the matrix to compare to
	* @return True iff matrices are notequal
	*/
	bool operator!=(const IntMatrix& other) const;


	/**
	 * @brief Calculates the Matrix transpose
	 * @return The IntMatrix transpose
	 */
	IntMatrix trans();

	/**
	 * @brief Check if the matrix is squared
	 * @param matrix - matrix to check
	 * @return True iff the matrix is squared, false otherwise
	 */
	bool isSquared() const;

	/**
	 * @brief Check if 2 matrices are of same dimensions
	 * @param first - 1st matrix to compare
	 * @param second - 2nd matrix to compare
	 * @return True iff they are of same dimensions, false otherwise
	 */
	bool isSameDimensions(const IntMatrix &second) const;

	/**
	 * @brief Check if 2 matrices are multiplaiable
	 * @param leftMatrix - 1st matrix to compare (left side)
	 * @param rightMatrix - 2nd matrix to compare (right side)
	 * @return True iff they are multipliable, false otherwise
	 */
	bool isMultipliable(const IntMatrix &rightMatrix) const;
	
	/**
	 * @brief Calculates the Matrix trace
	 * 		  for legal input (squared matrix)
	 * @return The IntMatrix trace
	 */
	int trace();
};
#endif //_INTMATRIX_H_


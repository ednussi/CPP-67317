/**
 * @file Matrix.hpp
 * @author  ednussi
 * @version 1.0
 * @date 9 Aug 2015
 *
 * @brief A defeniation of a generic Matrix API
 *
 * @section LICENSE
 * This program is a free software. You can freely redistribute it.
 *
 * @section DESCRIPITON
 * Matrix ix a class represnting a 2D matrix of any generic type which support
 * the operators *,-,+,=,==,!=,<<, which are overriten in the class
 * additional functionalities are also provided
 */

#ifndef _INTMATRIX_GENERIC_H_
#define _INTMATRIX_GENERIC_H_

#include <vector>
#include <iostream>
#include "Complex.h"
#include <stdexcept>
#include <thread>

#define NOT_SQUARED "ERROR: The Matrix entered is not sqaured."
#define NOT_SAME_DIMENSIONS "ERROR: The Matrices entered are not of the same dimensions."
#define NOT_MULTIPLAIABLE "ERROR: The Matrices entered are not of Multiplaiable dimensions."
#define OUT_OF_BORDERS "ERROR: The Place is unreachable - Out of Matrix borders"
#define UNLOGICAL_DIMESNSIONS "ERROR: Matrix dimensions of Rows/Cols cannot be set one to 0 and the other positive"
#define MATRIX_DOES_NOT_FIT_DIMENSIONS "ERROR: Dimensions do not fit the size of recieved matrix"
#define CHANGE_MODE(mode) "Generic Matrix mode changed to " << mode << " mode."

static bool s_isParallel = false;

/**
* IntMatrix class is a class representing a 2D matrix of integers and
* tools to work with 2D matrices.
*/
template <typename T> class Matrix
{
private:
    unsigned int _rows, _cols;
    std::vector<T> _cells;

    /**
    * @brief Check if 2 matrices are of same dimensions
    * @param first - 1st matrix to compare
    * @param second - 2nd matrix to compare
    * @return True iff they are of same dimensions, false otherwise
    */
    bool _isSameDimensions(const Matrix<T> &second) const
    {
        return ((_rows == second._rows) &&
            (_cols == second._cols));
    }

    /**
	* @brief Check if 2 matrices are multiplaiable
	* @param rightMatrix - matrix to compare (right side side)
	* @return True iff they are multipliable, false otherwise
	*/
	bool _isMultipliable(const Matrix<T> &rightMatrix) const
	{
		return (_cols == rightMatrix._rows);
	}

    /**
	* @brief Check if matrix is of logical Dimensions
	* @param rows - number of rows
    * @param cols - number of cols
	* @return True iff is of logical Dimensions, false otherwise
	*/
	bool _isLogicalDimensions(unsigned int rows, unsigned int cols) const
	{
        if ((rows == 0 && cols != 0) || ( cols == 0 && rows != 0))
        {
            if (rows == 0 && cols == 0)
            {
                return true;
            }
            return false;
        }
        return true;
	}

    /**
	* @brief Calculates addition of a single row between matrices
	* @param matrix - the matrix to add to from this matrix
    * @param row - number of cols
	*/
    void _addSingleRow(Matrix &matrix, unsigned int row) const
    {
        for (unsigned int col = 0; col < _cols; col++)
        {
            matrix(row, col) += (*this)(row, col);
        }
    }

    /**
	* @brief Calculates multiplacation of a single row between matrices
	* @param matrix - the matrix to insert the data into
	* @param other - the matrix to multiply with this matrix
    * @param row - number of cols
	*/
    void _multiplySingleRow(Matrix &matrix, const Matrix &other, unsigned int row) const
    {
        for (unsigned int col = 0; col < _cols; col++)
        {
            T sum = T();
            for (unsigned int intersec = 0; intersec < other._rows; intersec++)
            {
                sum += (*this)(row, intersec) * other(intersec, col);
            }
            matrix(row, col) = sum;
        }
    }

public:

    /**
	* @brief Sets the calculations to be done by parllel threads or not
	* @param setParallelisem - matrix to compare (right side side)
	* @return True iff they are multipliable, false otherwise
	*/
    static void setParallel(bool setParallelisem)
    {
        if (setParallelisem != s_isParallel)
        {
            std::string mode;
            if (setParallelisem)
            {
                mode = "parallel";
            }
            else
            {
                mode = "non-parallel";
            }

            std::cout << CHANGE_MODE(mode) << std::endl;
            s_isParallel = setParallelisem;
        }
    }

    /**
	* @brief Check if the matrix is squared
	* @param matrix - matrix to check
	* @return True iff the matrix is squared, false otherwise
	*/
	bool isSquareMatrix() const
	{
		return (_rows == _cols);
	}

    //_______________________________Constructers_________________________________

    /**
    * @brief Constructor
    * @param rows - number of rows of the matrix
    * @param cols - number of cols of the matrix
    * @param cells - the matrix itself
    */
    Matrix<T>(unsigned int rows, unsigned int cols, const std::vector<T> &cells)
    {
        if ((rows == 0 && cols != 0) || ( cols == 0 && rows != 0))
        {
            throw std::invalid_argument(UNLOGICAL_DIMESNSIONS);
        }

        if (rows * cols != cells.size())
        {
            throw std::invalid_argument(MATRIX_DOES_NOT_FIT_DIMENSIONS);
        }

        _rows = rows;
        _cols = cols;
        _cells = cells;
    }

    /**
    * @brief Copy Constructor
    * @param rows - number of rows of the matrix
    * @param cols - number of cols of the matrix
    */
    Matrix<T>(unsigned int rows, unsigned int cols) : Matrix<T>(rows, cols,
                                                      std::vector<T>(rows * cols))
    {
    }

    /**
    * @brief Default Constructor
    */
    Matrix<T>() : Matrix<T>(1, 1){ }

    /**
    * @brief Copy Constructor
    * @param matrixToCopy - A Matrix to make a copy of
    */
    Matrix<T>(const Matrix<T> &matrixToCopy) : Matrix<T>(matrixToCopy._rows,
                                         matrixToCopy._cols, matrixToCopy._cells) // (const std::vector<T>)
    {
    }

    /**
    * @brief Swap matrices
    * @param first - A Matrix to swap
    * @param second - A Matrix to swap
    */
    friend void swap(Matrix<T> &first, Matrix<T> &second)
    {
        std::swap(first._rows, second._rows);
        std::swap(first._cols, second._cols);
        std::swap(first._cells, second._cells);
    }

    /**
    * @brief Move Constructor
    * @param other - The other Matrix to move to
    */
    Matrix<T>(Matrix<T> && other) : _rows(std::move(other._rows)),
                             _cols(std::move(other._cols)),
                             _cells(std::move(other._cells))
    {
    }

    /**
    * @brief Default destructor
    */
    ~Matrix<T>()
    {
    }

    //_______________________________Getters_________________________________
    /**
    * @brief rows getter
    * @return number of rows of the matrix
    */
    unsigned int rows() const
    {
        return _rows;
    }

    /**
    * @brief cols getter
    * @return number of cols of the matrix
    */
    unsigned int cols() const
    {
        return _cols;
    }
    //_______________________________Iterators_________________________________
    typedef typename std::vector<T>::const_iterator const_iterator;

    /**
    * @brief returns an iterator to the beginning
    * @return a const iterator to the beginning of the matrix
    */
    const_iterator begin() const
    {
        return _cells.cbegin();
    }

    /**
    * @brief returns an iterator to the end
    * @return a const iterator to the end of the matrix
    */
    const_iterator end() const
    {
        return _cells.cend();
    }


    //_______________________________Operators_________________________________
    /**
    * @brief Override '=' operator for class
    * @param other - the matrix to assign from
    * @return IntMatrixOld with same data memebers as the assign from matrix
    */
    Matrix<T>& operator=(Matrix<T> other)
    {
        swap(*this, other);
        return *this;
    }

    /**
    * @brief Override '<<' operator for class
    * @param other - the matrix to print out
    * @param os - the output stream to enter the data to print to
    * @return reference to the stream after printing out the matrix
    */
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& other)
    {

        unsigned int colCounter = 0;
        for (const_iterator it = other.begin(); it != other.end(); it++)
        {
            os << *it << "\t";
            colCounter++;

            if (colCounter == other._cols)
            {
                os << std::endl;
                colCounter = 0;
            }
        }
        return os;
    }

    /**
    * @brief runs add using threads
    * @param other - the matrix to add it's data members
    * @return Matrix with the summed up data memebers
    */
    Matrix parallelAdd(const Matrix& other) const
    {
        Matrix result(other);

        std::vector<std::thread> rowsThreads(_rows);

        //initialize threads - each with uniqe line
        for (unsigned int row = 0; row < _rows; row++)
        {
            rowsThreads[row] = std::thread(&Matrix<T>::_addSingleRow, this,
                                           std::ref(result), row);
        }

        //wait for all running threads to finish
        for (unsigned int row = 0; row < _rows; row++)
        {
            (rowsThreads.at(row)).join();
        }

        return result;
    }

    /**
    * @brief Override '+' operator for class
    * @param other - the matrix to add it's data members
    * @return Matrix with the summed up data memebers
    */
    Matrix operator+(const Matrix& other) const
    {
        if (!this->_isSameDimensions(other))
        {
            throw std::invalid_argument(NOT_SAME_DIMENSIONS);
        }

        Matrix result(other);

        if (s_isParallel)
        {
            return parallelAdd(other);
        }
        else
        {
            for (unsigned int row = 0; row < _rows; row++)
            {
                _addSingleRow(result, row);
            }
        }
        return result;
    }

    /**
    * @brief Override '-' operator for class
    * @param other - the matrix to subtract it's data members
    * @return IntMatrixOld with the subtracted down data memebers
    */
    Matrix operator-(const Matrix& other) const
    {
        if (!this->_isSameDimensions(other))
        {
            throw std::invalid_argument(NOT_SAME_DIMENSIONS);
        }

        Matrix result(*this);
        for (unsigned int index = 0; index < _rows*_cols; index++)
        {
            result._cells[index] -= other._cells[index];
        }
        return result;
    }

    /**
    * @brief Override '()' operator for class - making like 2D arrys
    * @param row - the row the wanted Template object is at
    * @param col - the col the wanted Template object is at
    * @return T - the wanted in objects in that location
    */
    T& operator()(const unsigned int row, const unsigned int col)
    {
        if (row > _rows || col > _cols)
        {
            throw std::out_of_range(OUT_OF_BORDERS);
        }

        return _cells[(row) * _cols + col];
    }

    /**
    * @brief Override '()' operator for class - making like 2D arrys
    * @param row - the row the wanted Template object is at
    * @param col - the col the wanted Template object is at
    * @return const T - the wanted in objects in that location
    */
    const T operator()(const unsigned int row, const unsigned int col) const
    {
        if (row > _rows || col > _cols)
        {
            throw std::out_of_range(OUT_OF_BORDERS);
        }

        return _cells[(row) * _cols + col];
    }

    /**
    * @brief runs multiply using threads
    * @param other - the matrix to add it's data members
    * @param result - the matrix to add to the data members
    * @return Matrix with the summed up data memebers
    */
    Matrix parallelMultiply(Matrix& result, const Matrix& other) const
    {
        std::vector<std::thread> rowsThreads(_rows);

        //initialize threads - each with uniqe line
        for (unsigned int row = 0; row < _rows; row++)
        {
            rowsThreads[row] = std::thread(&Matrix<T>::_multiplySingleRow, this,
                                           std::ref(result), std::ref(other), row);
        }

        //wait for all threads to finish
        for (unsigned int row = 0; row < _rows; row++)
        {
            (rowsThreads.at(row)).join();
        }

        return result;
    }

    /**
    * @brief Override '*' operator for class
    * @param other - the matrix to multiply with it's data members
    * @return IntMatrixOld with the multiplication product of their data memebers
    */
    Matrix operator*(const Matrix& other) const
    {
        if (!this->_isMultipliable(other))
        {
            throw std::invalid_argument(NOT_MULTIPLAIABLE);
        }

        Matrix result(_rows, other._cols);

        if (s_isParallel)
        {
            return parallelMultiply(result, other);
        }

        for (unsigned int row = 0; row <  _rows; row++)
        {
            _multiplySingleRow(result, other, row);
        }

        return result;
    }

    /**
    * @brief Override '==' operator for class
    * @param other - the matrix to compare to
    * @return True iff matrices are equal
    */
    bool operator==(const Matrix& other) const
    {
        if (this == &other)
        {
            return true;
        }

        if (this->_isSameDimensions(other))
        {
            for (unsigned int row = 0; row < _rows; row++)
            {
                for (unsigned int column = 0; column < _cols; column++)
                {
                    if ((*this)(row, column) != other(row, column))
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    /**
    * @brief Override '!=' operator for class
    * @param other - the matrix to compare to
    * @return True iff matrices are not equal
    */
    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    /**
    * @brief Calculates the Matrix transpose
    * @return The IntMatrixOld transpose
    */
    Matrix<T> trans() const
    {
        Matrix transMatrix(_cols, _rows);

        for (unsigned int row = 0; row < _cols; row++)
        {
            for (unsigned int col = 0; col < _rows; col++)
            {
                transMatrix(row, col) = (*this)(col, row);
            }
        }
        return transMatrix;
    }

    /**
    * @brief Calculates the Matrix trace
    * 		  for legal input (squared matrix)
    * @return The Matrix trace
    */
    T trace() const
    {
        if (!this->isSquareMatrix())
        {
            throw std::invalid_argument(NOT_SQUARED);
        }

        T result = T();
        for (unsigned int diagnel = 0; diagnel < _rows; diagnel++)
        {
            result += (*this)(diagnel, diagnel);
        }

        return result;
    }

};

/**
* @brief Calculates the Matrix complex transpose
* @return The Matrix complex transpose
*/
template<>
inline Matrix<Complex> Matrix<Complex>::trans() const
{
    Matrix hermitianTransMatrix(_cols, _rows);

    for (unsigned int row = 0; row < _cols; row++)
    {
        for (unsigned int col = 0; col < _rows; col++)
        {
            hermitianTransMatrix(row, col) = (*this)(col, row).conj();
        }
    }
    return hermitianTransMatrix;
}

#endif //_INTMATRIX_GENERIC_H_

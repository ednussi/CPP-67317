/**
 * @file IntMatrixDriver.cpp
 * @author  ednussi
 * @version 1.0
 * @date 21 Aug 2015
 * 
 * @brief The Main function which runs the program

 * @section LICENSE
 * This program is a free software. You can freely redistribute it.
 *
 * @section DESCRIPTION
 * Using user input of specified format makes
 * one out of the 5 given availabe operations for those matrices
 */

//_____________INCLUDES_______________
#include <iostream>
#include "IntMatrix.h"
#include <sstream>
#include <assert.h> 

//___________DEFINIATIONS_____________
#define MENU_OPTIONS "1. add\n2. sub\n3. mul\n4. trans\n5. trace\n"
#define OPEN_MESSAGE "Choose operation:\n"
#define RESUALT_MESSAGE "==========\nResulted matrix:\n\n"
#define UPPER_BOUNDARY 5
#define LOWER_BOUNDARY 1
#define ONE_MATRIX_METHOD_MIN_NUMBER 4
#define TWO_MATRICES_METHODS_MESSAGE(operation) \
 "Operation " << operation << " requires 2 operand matrices."
#define ONE_MATRIX_METHOD_MESSAGE(operation) \
 "Operation " << operation << " requires 1 operand matrix."
#define DIFFRENET_DIMENSION_ERROR_MESSAGE(opearation) \
 "Error: " << opearation << " failed - different dimensions.\n"
#define DELIMINATOR ','
#define ADD_OP 1
#define SUB_OP 2 											          
#define MUL_OP 3
#define TRANS_OP 4
#define TRACE_OP 5
#define ADD_CMD "add"
#define SUB_CMD "sub"										          
#define MUL_CMD "mul"
#define TRANS_CMD "trans"
#define TRACE_CMD "trace"

using namespace std;

/**
 * @brief Creates a matrix
 * 		  According to the given logic of the format of inputs bu user
 *		  Turns the input data into matrix of the want IntMatrix type
 * @return The newly created matrix
 */
IntMatrix *createMatrix()
{
	int matrixRows, matrixColumns;
	string inputRowData;

	cout << "number of rows:";
	cin >> matrixRows;

	cout << "number of columns:";
	cin >> matrixColumns;

	cout << "Now insert the values of the matrix, row by row." << endl \
		<< "After each cell add the char ',' (including after the last cell of a row)." << endl \
		<< "Each row should be in a separate line." << endl;

	//initialize empty 2D intArray
	int** intArray = new int*[matrixRows]();
	assert(intArray != nullptr);
	for (int rowsIndex = 0; rowsIndex < matrixRows; rowsIndex++)
	{
		intArray[rowsIndex] = new int[matrixColumns]();
		assert(intArray != nullptr);
	}

	//insert data into the array
	string cellData;
	int column = 0;

	for (int row = 0; row < matrixRows; row++)
	{
		cin >> inputRowData;
		istringstream dataStream(inputRowData);
		while (getline(dataStream, cellData, DELIMINATOR))
		{
			intArray[row][column] = stoi(cellData);
			column++;
		}
		column = 0;
	}

	//create the Intmatrix object
	IntMatrix *myMatrix = new IntMatrix(matrixRows, matrixColumns, (const int**) intArray);
	assert(myMatrix != nullptr);

	//delete intArray
	for (int index = 0; index < matrixRows; index++)
	{
		delete[] intArray[index];
	}
	delete[] intArray;

	return myMatrix;
}

/**
 * @brief Check if an int is not within range
 * @param num - the int to check
 * @return True iff not in range, false otherwise
 */
bool notInRange(int num)
{
	return (num > UPPER_BOUNDARY || num < LOWER_BOUNDARY);
}

/**
 * @brief Check if methodNum belongs to method which uses one matrix
 * @param methodNum - the methodNum to check
 * @return True iff methodNum uses one matrix, false otherwise
 */
bool isOneMatrixMethod(int methodNum)
{
	return (methodNum >= ONE_MATRIX_METHOD_MIN_NUMBER);
}

/**
 * @brief Runs the addFunc method program
 * @param firstMatrix - the left matrix to run the oprand on
 * @param secondMatrix - the right matrix to run the oprand on
 */
void addFunc(IntMatrix firstMatrix, IntMatrix secondMatrix)
{
	if (firstMatrix.isSameDimensions(secondMatrix))
	{
		cout << RESUALT_MESSAGE;
		cout << (firstMatrix += secondMatrix) << endl;
	}
	else
	{
		cout << DIFFRENET_DIMENSION_ERROR_MESSAGE(ADD_CMD);
	}
}

/**
 * @brief Runs the subFunc method program
 * @param firstMatrix - the left matrix to run the oprand on
 * @param secondMatrix - the right matrix to run the oprand on
 */
void subFunc(IntMatrix firstMatrix, IntMatrix secondMatrix)
{
	if (firstMatrix.isSameDimensions(secondMatrix))
	{
		cout << RESUALT_MESSAGE;
		cout << (firstMatrix -= secondMatrix) << endl;
	}
	else
	{
		cout << DIFFRENET_DIMENSION_ERROR_MESSAGE(SUB_CMD);
	}
}

/**
 * @brief Runs the mulFunc method program
 * @param firstMatrix - the left matrix to run the oprand on
 * @param secondMatrix - the right matrix to run the oprand on
 */
void mulFunc(IntMatrix firstMatrix, IntMatrix secondMatrix)
{
	if (firstMatrix.isMultipliable(secondMatrix))
	{
		cout << RESUALT_MESSAGE;
		cout << (firstMatrix *= secondMatrix) << endl;
	}
	else
	{
		cout << DIFFRENET_DIMENSION_ERROR_MESSAGE(MUL_CMD);
	}	
}

/**
 * @brief Runs the transFunc method program
 * @param matrix - the matrix to run the func on
 */
void transFunc(IntMatrix matrix)
{
	cout << RESUALT_MESSAGE;
	cout << matrix.trans() << endl;
}

/**
 * @brief Runs the traceFunc method program
 * @param matrix - the matrix to run the func on
 */
void traceFunc(IntMatrix matrix)
{
	if (matrix.isSquared())
	{
		cout << "The matrix is square and its trace is " << matrix.trace() << endl;
		
	}
	else
	{
		cout << "Error: trace failed - The matrix isn't square." << endl;
	}	
}

/**
 * @brief Runs the One Matrix methods program
 * @param methodNum - the methodNum
 */
void runOneMatrixMethods(int methodNum)
{
	string op;
	void(*oneMatrixFunc)(IntMatrix) = NULL;

	switch (methodNum)
	{
		case TRANS_OP:
			op = TRANS_CMD;
			oneMatrixFunc = transFunc;
			break;
		case TRACE_OP:
			op = TRACE_CMD;
			oneMatrixFunc = traceFunc;
			break;
	}

	cout << ONE_MATRIX_METHOD_MESSAGE(op) << endl;
	IntMatrix *pMyMatrix = createMatrix();
	cout << "--------" << endl << "got matrix:" << endl << endl;
	cout << *pMyMatrix << endl;

	oneMatrixFunc(*pMyMatrix);
	delete(pMyMatrix);
	pMyMatrix = nullptr;
}

/**
 * @brief Runs the Two Matrices methods program
 * @param methodNum - the methodNum
 */
void runTwoMatricesMethods(int methodNum)
{
	string op;
	void(*twoMatricesFunc)(IntMatrix, IntMatrix) = NULL;

	switch (methodNum)
	{
		case ADD_OP:
			op = ADD_CMD;
			twoMatricesFunc = addFunc;
			break;
		case SUB_OP:
			op = SUB_CMD;
			twoMatricesFunc = subFunc;
			break;
		case MUL_OP:
			op = MUL_CMD;
			twoMatricesFunc = mulFunc;
			break;
	}

	cout << TWO_MATRICES_METHODS_MESSAGE(op) << endl;

	cout << "Insert first matrix:" << endl;
	IntMatrix *firstMatrix = createMatrix();
	
	cout << "Insert second matrix:" << endl;
	IntMatrix *secondMatrix = createMatrix();

	cout << "--------" << endl << "Got first matrix:" << endl << endl;
	cout << *firstMatrix << endl;
	cout << "--------" << endl << "Got second matrix:" << endl << endl;
	cout << *secondMatrix << endl;

	twoMatricesFunc(*firstMatrix, *secondMatrix);
	delete(firstMatrix);
	delete(secondMatrix);
	firstMatrix = nullptr;
	secondMatrix = nullptr;
}

int main()
{
	int input = 0;
	IntMatrix a;

	while (notInRange(input))
	{
		cout << OPEN_MESSAGE << MENU_OPTIONS;
		cin >> input;
	}

	if (isOneMatrixMethod(input))
	{
		runOneMatrixMethods(input);

	}
	else
	{
		runTwoMatricesMethods(input);
	}
	return 0;
}
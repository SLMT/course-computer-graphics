// Our libraries
#include "matrix.h"

Matrix::Matrix() {
	// Initialize as an indentity matrix
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				_data[i][j] = 1;
			else
				_data[i][j] = 0;
		}
	}
}

void Matrix::multiply(Matrix &rightMatrix) {
	this->multiply(rightMatrix._data);
}

void Matrix::multiply(GLfloat rightMatrix[][4]) {
	// Temp result matrix
	GLfloat result[4][4];

	// Initialize result matrix
	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
			result[i][j] = 0;

	// Matrix multiplication
	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                result[i][j] = result[i][j] + 
					_data[i][k] * rightMatrix[k][j];

	// Copy result
	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
			_data[i][j] = result[i][j];
}

void Matrix::outputAsColumnMajor(GLfloat *out) {
	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
			out[i + j * 4] = _data[i][j];
}

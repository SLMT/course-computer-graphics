#include <stdio.h>
#include <math.h>

// Our libraries
#include "matrix.h"

#define PI 3.14159265


/*************************
  Static factory methods
**************************/

Matrix Matrix::generateTranslationMatrix(GLfloat dx, GLfloat dy, GLfloat dz) {
	Matrix matrix = Matrix();

	GLfloat trans[4][4] = {
		{1, 0, 0, dx},
		{0, 1, 0, dy},
		{0, 0, 1, dz},
		{0, 0, 0, 1}
	};
	matrix.postmultiply(trans);

	return matrix;
}

Matrix Matrix::generateRotationMatrix(GLfloat theta, GLfloat x, GLfloat y, GLfloat z) {
	Matrix matrix = Matrix();

	GLfloat sinTheta = (GLfloat) sin(theta * PI / 180);
	GLfloat cosTheta = (GLfloat) cos(theta * PI / 180);
	GLfloat xs = x * sinTheta;
	GLfloat ys = y * sinTheta;
	GLfloat zs = z * sinTheta;
	
	GLfloat rotate[4][4] = {
		{x * x * (1 - cosTheta) + cosTheta, x * y * (1 - cosTheta) - zs, x * z * (1 - cosTheta) + ys, 0},
		{y * x * (1 - cosTheta) + zs, y * y * (1 - cosTheta) + cosTheta, y * z * (1 - cosTheta) - xs, 0},
		{x * z * (1 - cosTheta) - ys, y * z * (1 - cosTheta) + xs, z * z * (1 - cosTheta) + cosTheta, 0},
		{0, 0, 0, 1}
	};
	matrix.postmultiply(rotate);

	return matrix;
}

Matrix Matrix::generateScaleMatrix(GLfloat sx, GLfloat sy, GLfloat sz) {
	Matrix matrix = Matrix();

	GLfloat scale[4][4] = {
		{sx, 0, 0, 0},
		{0, sy, 0, 0},
		{0, 0, sz, 0},
		{0, 0, 0, 1}
	};
	matrix.postmultiply(scale);

	return matrix;
}


/****************
  Class methods
*****************/

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

Matrix::Matrix(GLfloat rightMatrix[][4]) {
	// Initialize as an indentity matrix
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			_data[i][j] = rightMatrix[i][j];
}

void Matrix::postmultiply(Matrix &rightMatrix) {
	this->postmultiply(rightMatrix._data);
}

void Matrix::postmultiply(GLfloat rightMatrix[][4]) {
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

void Matrix::applyTo(GLfloat *vec) {
	GLfloat tmp[] = {0.0, 0.0, 0.0, 0.0};

	// Calculate
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			tmp[i] += vec[j] * _data[i][j];

	// Copy results
	for (int i = 0; i < 4; i++)
		vec[i] = tmp[i];
}

void Matrix::outputAsColumnMajor(GLfloat *out) {
	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
			out[i + j * 4] = _data[i][j];
}

void Matrix::printOut() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%f ", _data[i][j]);
		}
		printf("\n");
	}
}

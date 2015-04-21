#ifndef MATRIX_H
#define MATRIX_H

#include "freeglut\glut.h"

class Matrix {
public:

	// Constructor
	Matrix();

	// Multiply to this matrix
	void multiply(Matrix &rightMatrix);
	void multiply(GLfloat rightMatrix[][4]);

	// Translate to column major matrix
	void outputAsColumnMajor(GLfloat *out);


private:

	// Matrix data
	GLfloat _data[4][4];

};


#endif
#ifndef MATRIX_H
#define MATRIX_H

// 3-party libraries
#include <GL/glew.h>

class Matrix {
public:

	// Static factory methods
	static Matrix generateTranslationMatrix(GLfloat dx, GLfloat dy, GLfloat dz);
	static Matrix generateRotationMatrix(GLfloat theta, GLfloat x, GLfloat y, GLfloat z);
	static Matrix generateScaleMatrix(GLfloat sx, GLfloat sy, GLfloat sz);

	// Constructors
	Matrix();
	Matrix(GLfloat rightMatrix[][4]);

	// Multiply to this matrix
	void postmultiply(Matrix &rightMatrix);
	void postmultiply(GLfloat rightMatrix[][4]);

	// Translate to column major matrix
	void outputAsColumnMajor(GLfloat *out);

	// Print the matrix to system standard output
	void printOut();

private:

	// Matrix data
	GLfloat _data[4][4];

};


#endif
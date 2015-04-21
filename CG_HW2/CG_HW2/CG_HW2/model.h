#ifndef MODEL_H
#define MODEL_H

// Our libraries
#include "matrix.h"

class Model {
public:

	// Constructor
	Model(char *fileName);

	// Deconstructor
	~Model();

	// Render function
	void draw(const Matrix &transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc);

private:

	// Model data
	GLuint *_vIndices;
	GLfloat *_vertices, *_colors;
	GLsizei _numTriangles;

	// Matrixes for rendering
	Matrix _translate, _rotate, _scale;
};


#endif
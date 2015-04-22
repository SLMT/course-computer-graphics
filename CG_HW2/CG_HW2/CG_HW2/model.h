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
	void draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc);

private:

	// Model data
	GLuint *_vIndices;
	GLfloat *_vertices, *_colors;
	GLsizei _numTriangles, _numVertices;

	// Matrixes for rendering
	Matrix _normalize;
	Matrix _translate, _rotate, _scale;

};


#endif
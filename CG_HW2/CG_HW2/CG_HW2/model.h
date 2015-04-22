#ifndef MODEL_H
#define MODEL_H

// Our libraries
#include "matrix.h"

// 3-party libraries
#include <GL/glew.h>

class Model {
public:

	// Constructor
	Model(char *fileName);

	// Deconstructor
	~Model();

	// Transform functions
	void translate(GLfloat dx, GLfloat dy, GLfloat dz);
	void rotate(GLfloat theta, GLfloat x, GLfloat y, GLfloat z);
	void scale(GLfloat sx, GLfloat sy, GLfloat sz);

	// Render function
	void draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc);

private:

	// Model data
	GLuint *_vIndices;
	GLfloat *_vertices, *_colors;
	GLsizei _numTriangles, _numVertices;

	// Matrixes for rendering
	Matrix _normalize;
	Matrix _translattion, _rotation, _scale;

};


#endif
#ifndef CAMARA_H
#define CAMARA_H

// Our libraries
#include "matrix.h"

// 3-party libraries
#include <GL/glew.h>

class Camara {
public:

	// Constructor
	Camara();

	// Transfrom functions
	void moveEye(GLfloat dx, GLfloat dy, GLfloat dz);
	void moveCenter(GLfloat dx, GLfloat dy, GLfloat dz);
	void moveUp(GLfloat dx, GLfloat dy, GLfloat dz);

	// Getter
	Matrix getViewTransform();

private:

	// Generate transfrom matrix
	void calculateTransformMatrix();

	GLfloat _eye[3], _center[3], _up[3];

	Matrix _viewTransfrom;
}


#endif
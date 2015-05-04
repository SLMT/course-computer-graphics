#ifndef PROJECTION_H
#define PROJECTION_H

// Our libraries
#include "matrix.h"

// 3-party libraries
#include <GL/glew.h>

class Projection {
public:

	// Constructor
	Projection(bool isPerspective,
		GLfloat left, GLfloat right,
		GLfloat bottom, GLfloat top,
		GLfloat near, GLfloat far);

	// Getter
	inline Matrix getProjectTransfrom() {
		return _projectTransfrom;
	}

	// Toggle functions
	void toggleProjectionMode();

private:

	void orthoProject();
	void perspectiveProject();

	// Projection info
	bool isPerspective;
	GLfloat left, right, bottom, top, near, far;

	// Transform matrix
	Matrix _projectTransfrom;
};

#endif
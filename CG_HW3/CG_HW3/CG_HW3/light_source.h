#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

// Our libraries
#include "shader.h"

// 3-party libraries
#include <GL/glew.h>

class LightSource {
public:

	// Constructor
	LightSource(GLfloat initX, GLfloat initY, GLfloat initZ);

	// Moving functions
	void rotateByX(GLfloat theta);
	void rotateByY(GLfloat theta);
	void rotateByZ(GLfloat theta);

	// Render functions
	void linkShader(ShaderPointers shPos);

private:

	// Position
	GLfloat _position[4];

	// Color paramters
	GLfloat _ambient[4], _diffuse[4], _specular[4];
};

#endif
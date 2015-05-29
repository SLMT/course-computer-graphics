#include <stdio.h>

// Our libraries
#include "light_source.h"
#include "matrix.h"

LightSource::LightSource(GLfloat initX, GLfloat initY, GLfloat initZ) {

	// Set up the position
	_position[0] = initX;
	_position[1] = initY;
	_position[2] = initZ;
	_position[3] = 0.0f;

	// Set up lighting paramters
	for (int i = 0; i < 4; i++) {
		_ambient[i] = 1.0f;
		_diffuse[i] = 1.0f;
		_specular[i] = 1.0f;
	}
}

void LightSource::rotateByX(GLfloat theta) {
	Matrix rotate = Matrix::generateRotationMatrix(theta, 1.0, 0.0, 0.0);
	rotate.applyTo(_position);
}

void LightSource::rotateByY(GLfloat theta) {
	Matrix rotate = Matrix::generateRotationMatrix(theta, 0.0, 1.0, 0.0);
	rotate.applyTo(_position);
}

void LightSource::rotateByZ(GLfloat theta) {
	Matrix rotate = Matrix::generateRotationMatrix(theta, 0.0, 0.0, 1.0);
	rotate.applyTo(_position);
}


void LightSource::linkShader(ShaderPointers shPos) {
	glUniform4fv(shPos.lightPos, 1, _position);

	glUniform4fv(shPos.lightAmb, 1, _ambient);
	glUniform4fv(shPos.lightDiff, 1, _diffuse);
	glUniform4fv(shPos.lightSpec, 1, _specular);
}
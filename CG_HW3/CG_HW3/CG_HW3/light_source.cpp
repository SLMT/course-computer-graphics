#include <stdio.h>

// Our libraries
#include "light_source.h"
#include "matrix.h"

LightSource::LightSource(LightType type, bool isEnabled) {

	// Set up status
	_isEnabled = isEnabled;
	_type = type;

	// Set up position
	if (type == Directional) {
		_position[0] = -1.0f;
		_position[1] = -1.0f;
		_position[2] = -1.0f;
	} else {
		_position[0] = 1.0f;
		_position[1] = 1.0f;
		_position[2] = 1.0f;
	}

	// Set up color
	for (int i = 0; i < 4; i++) {
		_ambient[i] = 1.0f;
		_color[i] = 1.0f;
	}

	// Set up spot light parameters
	_spotDirect[0] = -1.0f;
	_spotDirect[1] = -1.0f;
	_spotDirect[2] = -1.0f;
	_spotExp = 1.0f;
	_spotCosCutoff = 0.001f;
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
	switch (_type) {
	case Directional:
		if (_isEnabled)
			glUniform1i(shPos.dirEnabled, 1);
		else
			glUniform1i(shPos.dirEnabled, 0);
		glUniform3fv(shPos.dirDirection, 1, _position);
		glUniform4fv(shPos.dirAmbient, 1, _ambient);
		glUniform4fv(shPos.dirColor, 1, _color);
		break;
	case Positional:
		if (_isEnabled)
			glUniform1i(shPos.posEnabled, 1);
		else
			glUniform1i(shPos.posEnabled, 0);
		glUniform3fv(shPos.posPosition, 1, _position);
		glUniform4fv(shPos.posAmbient, 1, _ambient);
		glUniform4fv(shPos.posColor, 1, _color);
		break;
	case SpotLight:
		if (_isEnabled)
			glUniform1i(shPos.spotEnabled, 1);
		else
			glUniform1i(shPos.spotEnabled, 0);
		glUniform3fv(shPos.spotPosition, 1, _position);
		glUniform4fv(shPos.spotAmbient, 1, _ambient);
		glUniform4fv(shPos.spotColor, 1, _color);
		glUniform3fv(shPos.spotDirection, 1, _spotDirect);
		glUniform1f(shPos.spotExponent, _spotExp);
		glUniform1f(shPos.spotCosCutoff, _spotCosCutoff);
		break;
	}
}

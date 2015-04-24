#include <math.h>

// Our libraries
#include "camara.h"

void normalize(GLfloat *vec, int count) {
	GLfloat tmp = 0;
	for (int i = 0; i < count; i++)
		tmp += vec[i] * vec[i];
	tmp = sqrt(tmp);
	for (int i = 0; i < count; i++)
		vec[i] /= tmp;
}


Camara::Camara() {
	// eye position
	_eye[0] = 0;
	_eye[1] = 0;
	_eye[2] = 0;

	// center location
	_center[0] = 0;
	_center[1] = 0;
	_center[2] = 0;

	// up vector
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
}

void Camara::moveEye(GLfloat dx, GLfloat dy, GLfloat dz) {
	_eye[0] += dx;
	_eye[1] += dy;
	_eye[2] += dz;
}

void Camara::moveCenter(GLfloat dx, GLfloat dy, GLfloat dz) {
	_center[0] += dx;
	_center[1] += dy;
	_center[2] += dz;
}

void Camara::moveUp(GLfloat dx, GLfloat dy, GLfloat dz) {
	_up[0] += dx;
	_up[1] += dy;
	_up[2] += dz;
}

void Camara::calculateTransformMatrix() {
	GLfloat forward[3], up[3], right[3], realUp[3], tmp;
	
	// Calculate forward vector
	for (int i = 0; i < 3; i++)
		forward[i] = _center[i] - _eye[i];
	normalize(forward, 3);

	// Get up vector
	for (int i = 0; i < 3; i++)
		up[i] = _up[i];
	normalize(up, 3);

	// Calculate right vector
	for (int i = 0; i < 3; i++)
		right[i] = forward[i] * up[i];
	normalize(right, 3);

	// Calculate u
	for (int i = 0; i < 3; i++)
		realUp[i] = right[i] * forward[i];
	normalize(realUp, 3);

	// Generate basis
	GLfloat view[4][4] = {
		{right[0], right[1], right[2], 0},
		{realUp[0], realUp[1], realUp[2], 0},
		{-forward[0], -forward[1], -forward[2], 0},
		{0, 0, 0, 1}
	};
	_viewTransfrom = Matrix(view);

	// Eye traslation
	Matrix eyeM = Matrix.generateTranslationMatrix(-_eye[0], -_eye[1], -_eye[2]);
	_viewTransfrom.postmultiply(eyeM);
}

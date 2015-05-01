#include <math.h>
#include <float.h>

// Our libraries
#include "camara.h"

void normalize(GLfloat *vec) {
	GLfloat tmp = 0;
	for (int i = 0; i < 3; i++)
		tmp += vec[i] * vec[i];
	tmp = sqrt(tmp);

	if (tmp > FLT_EPSILON)
		for (int i = 0; i < 3; i++)
			vec[i] /= tmp;
}

void crossProduct(GLfloat *vec1, GLfloat *vec2, GLfloat *result) {
	result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}


Camara::Camara(GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
	GLfloat centerX, GLfloat centerY, GLfloat centerZ,
	GLfloat upX, GLfloat upY, GLfloat upZ) {

	// eye position
	_eye[0] = eyeX;
	_eye[1] = eyeY;
	_eye[2] = eyeZ;

	// center location
	_center[0] = centerX;
	_center[1] = centerY;
	_center[2] = centerZ;

	// up vector
	_up[0] = upX;
	_up[1] = upY;
	_up[2] = upZ;

	calculateTransformMatrix();
}

void Camara::moveEye(GLfloat dx, GLfloat dy, GLfloat dz) {
	_eye[0] += dx;
	_eye[1] += dy;
	_eye[2] += dz;

	calculateTransformMatrix();
}

void Camara::moveCenter(GLfloat dx, GLfloat dy, GLfloat dz) {
	_center[0] += dx;
	_center[1] += dy;
	_center[2] += dz;

	calculateTransformMatrix();
}

void Camara::moveUp(GLfloat dx, GLfloat dy, GLfloat dz) {
	_up[0] += dx;
	_up[1] += dy;
	_up[2] += dz;

	calculateTransformMatrix();
}

Matrix Camara::getViewTransform() {
	return _viewTransfrom;
}

void Camara::calculateTransformMatrix() {
	GLfloat forward[3], up[3], right[3], realUp[3];
	
	// Calculate forward vector
	for (int i = 0; i < 3; i++)
		forward[i] = _center[i] - _eye[i];
	normalize(forward);

	// Get up vector
	for (int i = 0; i < 3; i++)
		up[i] = _up[i];
	normalize(up);

	// Calculate right vector
	crossProduct(forward, up, right);
	normalize(right);

	// Calculate real up vector
	crossProduct(right, forward, realUp);
	normalize(realUp);

	// Generate basis
	GLfloat view[4][4] = {
		{right[0], right[1], right[2], 0},
		{realUp[0], realUp[1], realUp[2], 0},
		{-forward[0], -forward[1], -forward[2], 0},
		{0, 0, 0, 1}
	};
	_viewTransfrom = Matrix(view);

	// Eye traslation
	Matrix eyeM = Matrix::generateTranslationMatrix(-_eye[0], -_eye[1], -_eye[2]);
	_viewTransfrom.postmultiply(eyeM);
}

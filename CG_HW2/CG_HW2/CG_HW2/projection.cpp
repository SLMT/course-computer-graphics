// Our libraries
#include "projection.h"

// Orthogonal Projection Constructor
Projection::Projection(bool isPerspective,
		GLfloat left, GLfloat right,
		GLfloat bottom, GLfloat top,
		GLfloat near, GLfloat far) {

	// Save info
	this->isPerspective = isPerspective;
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;

	if (isPerspective)
		perspectiveProject();
	else
		orthoProject();
}

void Projection::toggleProjectionMode() {
	isPerspective = !isPerspective;
	if (isPerspective)
		perspectiveProject();
	else
		orthoProject();
}

void Projection::orthoProject() {
	GLfloat tx = - (right + left) / (right - left);
	GLfloat ty = - (top + bottom) / (top - bottom);
	GLfloat tz = - (far + near) / (far - near);

	GLfloat e1 = 2 / (right - left);
	GLfloat e2 = 2 / (top - bottom);
	GLfloat e3 = -2 / (far - near);

	// Generate matrix
	GLfloat project[4][4] = {
		{e1, 0, 0, tx},
		{0, e2, 0, ty},
		{0, 0, e3, tz},
		{0, 0, 0, 1}
	};
	_projectTransfrom = Matrix(project);
}

void Projection::perspectiveProject() {
	GLfloat A = (right + left) / (right - left);
	GLfloat B = (top + bottom) / (top - bottom);
	GLfloat C = - (far + near) / (far - near);
	GLfloat D = -2 * far * near / (far - near);

	GLfloat e1 = 2 * near / (right - left);
	GLfloat e2 = 2 * near  / (top - bottom);

	// Generate matrix
	GLfloat project[4][4] = {
		{e1, 0, A, 0},
		{0, e2, B, 0},
		{0, 0, C, D},
		{0, 0, -1, 0}
	};
	_projectTransfrom = Matrix(project);
}

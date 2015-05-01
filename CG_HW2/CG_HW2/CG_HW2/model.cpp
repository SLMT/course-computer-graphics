#include <float.h>

// Our libraries
#include "model.h"

// 3-party libraries
#include "GLM.h"

Model::Model(char *fileName) {

	// ============
	//  Load model
	// ============

	// Load model
	GLMmodel *model = glmReadOBJ(fileName);

	// Save data
	_numTriangles = model->numtriangles;
	_numVertices = model->numvertices;

	_vIndices = new GLuint[_numTriangles * 3]; // 3 vertices per triangle
	_vertices = new GLfloat[_numVertices * 9]; // x, y, z per vertex
	_colors = new GLfloat[_numVertices * 9]; // r, g, b per pertex

	// Iterate each triangle
	for (GLsizei i = 0; i < _numTriangles; i++) {
		// Save indeices
		for (GLsizei j = 0; j < 3; j++) {
			// Notice: The indeces in Obj files start from 1
			_vIndices[i * 3 + j] = (model->triangles[i]).vindices[j] - 1;
		}
	}

	// Iterate each vertex
	for (GLsizei i = 0; i < _numVertices; i++) {
		// Fetch vertex and color
		for (unsigned j = 0; j < 3; j++) {
			// Notice: The indeces in Obj files start from 1
			_vertices[i * 3 + j] = model->vertices[(i + 1) * 3 + j];
			_colors[i * 3 + j] = model->colors[(i + 1) * 3 + j];
		}
	}

	// Free GLM model data
	glmDelete(model);


	// ===========================
	//  Generate normalize matrix
	// ===========================
	
	// Find the longest distance to the center
	GLfloat max_diff = 0;
	for (unsigned ci = 0; ci < 3; ci++) {
		GLfloat max = FLT_MIN, min = FLT_MAX;

		for (GLsizei vi = 0; vi < _numVertices; vi++) {
			GLfloat value = _vertices[vi * 3 + ci];

			if (max < value)
				max = value;

			if (min > value)
				min = value;
		}

		GLfloat diff = (max - min) / 2;
		if (max_diff < diff)
			max_diff = diff;
	}

	// Generate Scale matrix
	GLfloat ratio = 1.0f / max_diff;
	Matrix scaleMatrix = Matrix::generateScaleMatrix(ratio, ratio, ratio);

	// Find the center
	GLfloat center[3];
	for (unsigned ci = 0; ci < 3; ci++) {
		GLfloat max = -FLT_MAX, min = FLT_MAX;

		for (GLsizei vi = 0; vi < _numVertices; vi++) {
			GLfloat value = _vertices[vi * 3 + ci];

			if (max < value)
				max = value;

			if (min > value)
				min = value;
		}

		center[ci] = (max + min) / 2;
	}

	// Generate translate matrix
	Matrix transMatrix = Matrix::generateTranslationMatrix(-center[0], -center[1], -center[2]);

	// Calculate normailze matrix
	// N = I * S * T
	_normalize = Matrix();
	_normalize.postmultiply(scaleMatrix);
	_normalize.postmultiply(transMatrix);


	// ===================
	//  Initialize others
	// ===================

	// Initialize matrixes
	_translation = Matrix();
	_rotation = Matrix();
	_scale = Matrix();
}

Model::~Model() {
	// Release resource
	delete[] _vIndices;
	delete[] _vertices;
	delete[] _colors;
}

void Model::translate(GLfloat dx, GLfloat dy, GLfloat dz) {
	Matrix t = Matrix::generateTranslationMatrix(dx, dy, dz);
	_translation.postmultiply(t);
}

void Model::rotate(GLfloat theta, GLfloat x, GLfloat y, GLfloat z) {
	Matrix r = Matrix::generateRotationMatrix(theta, x, y, z);
	_rotation.postmultiply(r);
}

void Model::scale(GLfloat sx, GLfloat sy, GLfloat sz) {
	Matrix s = Matrix::generateScaleMatrix(sx, sy, sz);
	_scale.postmultiply(s);
}

void Model::draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc) {
	GLfloat mvp[16];

	// Calculate MVP
	// MVP = T * R * S * N
	transformMatrix.postmultiply(_translation);
	transformMatrix.postmultiply(_rotation);
	transformMatrix.postmultiply(_scale);
	transformMatrix.postmultiply(_normalize);
	transformMatrix.outputAsColumnMajor(mvp);

	// Pass matrix and array pointers
	glVertexAttribPointer(shPosLoc, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
	glVertexAttribPointer(shColLoc, 3, GL_FLOAT, GL_FALSE, 0, _colors);
	glUniformMatrix4fv(shMvpLoc, 1, GL_FALSE, mvp);

	// draw the array we just bound
	glDrawElements(GL_TRIANGLES, _numTriangles * 3, GL_UNSIGNED_INT, (GLvoid*)_vIndices);
}

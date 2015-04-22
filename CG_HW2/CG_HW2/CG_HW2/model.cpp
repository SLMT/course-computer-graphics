#include <float.h>

// 3-party libraries
#include <GL\glew.h>
#include "GLM.h"

// Our libraries
#include "model.h"

Model::Model(char *fileName) {

	// ============
	//  Load model
	// ============

	// Load model
	GLMmodel *model = glmReadOBJ(fileName);

	// Save data
	_numTriangles = model->numtriangles;
	_numVertices = model->numvertices;
	_vIndices = new GLuint[model->numtriangles * 3]; // 3 vertices per triangle
	_vertices = new GLfloat[model->numtriangles * 9]; // x, y, z per vertex
	_colors = new GLfloat[model->numtriangles * 9]; // r, g, b per pertex

	unsigned vi;
	// Iterate each triangle
	for (unsigned i = 0; i < model->numtriangles; i++) {
		// Iterate each vertex
		for (unsigned j = 0; j < 3; j++) {
			// Get an index
			vi = model->triangles->vindices[j];

			// Fetch vertex and color
			for (unsigned k = 0; k < 3; k++) {
				_vertices[i * 9 + j * 3 + k] = model->vertices[vi * 3 + k];
				_colors[i * 9 + j * 3 + k] = model->colors[vi * 3 + k];
			}

			// Save index
			// Notice: The indeces in Obj files start from 1
			_vIndices[i * 3 + j] = vi - 1;
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

		for (unsigned vi = 0; vi < _numVertices; vi++) {
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

		for (unsigned vi = 0; vi < _numVertices; vi++) {
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
	_translate = Matrix();
	_rotate = Matrix();
	_scale = Matrix();
}

Model::~Model() {
	// Release resource
	delete[] _vIndices;
	delete[] _vertices;
	delete[] _colors;
}

void Model::draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc) {
	GLfloat mvp[16];

	// TODO: Add translate, rotate, scale matrix

	// TODO: Add normalize matrix

	// Calculate mvp
	transformMatrix.postmultiply(_normalize);
	transformMatrix.outputAsColumnMajor(mvp);

	// Pass matrix and array pointers
	glVertexAttribPointer(shPosLoc, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
	glVertexAttribPointer(shColLoc, 3, GL_FLOAT, GL_FALSE, 0, _colors);
	glUniformMatrix4fv(shMvpLoc, 1, GL_FALSE, mvp);

	// draw the array we just bound
	glDrawElements(GL_TRIANGLES, _numTriangles * 3, GL_UNSIGNED_INT, (GLvoid*)_vIndices);
}

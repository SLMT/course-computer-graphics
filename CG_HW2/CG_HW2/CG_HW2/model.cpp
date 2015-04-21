// 3-party libraries
#include <GL\glew.h>
#include "GLM.h"
#include <stdio.h>
// Our libraries
#include "model.h"

Model::Model(char *fileName) {

	// Load model
	GLMmodel *model = glmReadOBJ(fileName);

	// Saving data
	_numTriangles = model->numtriangles;
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

void Model::draw(const Matrix &transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc) {

	// TODO: Add translate, rotate, scale matrix

	// TODO: Add normalize matrix

	// Pass matrix and array pointers
	glVertexAttribPointer(shPosLoc, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
	glVertexAttribPointer(shColLoc, 3, GL_FLOAT, GL_FALSE, 0, _colors);
	//glUniformMatrix4fv(shMvpLoc, 1, GL_FALSE, mvp->);

	// draw the array we just bound
	glDrawElements(GL_TRIANGLES, _numTriangles * 3, GL_UNSIGNED_INT, (GLvoid*)_vIndices);
}

#include <float.h>

// Our libraries
#include "model.h"

// 3-party libraries
#include "GLM.h"

void copyData(unsigned count, GLfloat *from, GLfloat *to) {
	for (int i = 0; i < count; i++)
		to[i] = from[i];
}

Model::Model(char *fileName) {

	// ============
	//  Load model
	// ============

	// Load model
	GLMmodel *model = glmReadOBJ(fileName);

	// Allocate memory for groups
	_numGroups = model->numgroups;
	_groups = new MaterialGroup[_numGroups];

	// Traverse groups
	for (GLMgroup* group = model->groups, unsigned groupIndex = 0;
	group; group = group->next, groupIndex++) {
		// Get material data
		GLuint matIndex = group->material;
		GLMmaterial mat = model->materials[matIndex];

		copyData(4, mat.diffuse, _groups[groupIndex].diffuse);
		copyData(4, mat.ambient, _groups[groupIndex].ambient);
		copyData(4, mat.specular, _groups[groupIndex].specular);
		copyData(4, mat.emmissive, _groups[groupIndex].emmissive);
		_groups[groupIndex].shininess = mat.shininess;

		// Allocate memory for vertices and normals
		GLuint numTri = group->numtriangles;
		_groups[groupIndex].numTriangles = numTri;
		_groups[groupIndex].vertices = new GLfloat[numTri * 3 * 3];
		_groups[groupIndex].normals = new GLfloat[numTri * 3 * 3];

		// Get vertices and normals
		for (GLuint triIndex = 0; triIndex < numTri; triIndex++) {
			// Get the triangle index in the GLM model
			GLuint glmTriIndex = group->triangles[triIndex];

			for (GLuint vecIndex = 0; vecIndex < 3; vecIndex++) {
				// Get the vectex index in the GLM model
				GLuint glmVecIndex = model->triangles[glmTriIndex].vindices[vecIndex];
				GLuint glmNorIndex = model->triangles[glmTriIndex].nindices[vecIndex];

				for (GLuint coordIndex = 0; coordIndex < 3; coordIndex++) {
					// Calculate the saving index
					GLuint saveIndex = triIndex * 9 + vecIndex * 3 + coordIndex;

					// Get data
					_groups[groupIndex].vertices[saveIndex] =
						model->vertices[glmVecIndex * 3 + coordIndex];
					_groups[groupIndex].normals[saveIndex] =
						model->normals[glmNorIndex * 3 + coordIndex];
				}
			}
		}
	}


	// ===========================
	//  Generate normalize matrix
	// ===========================
	
	// Find the longest distance to the center
	GLfloat max_diff = 0;
	for (unsigned ci = 0; ci < 3; ci++) {
		GLfloat max = FLT_MIN, min = FLT_MAX;

		// Notice: The indeces in Obj files start from 1
		for (GLsizei vi = 1; vi < model->numvertices; vi++) {
			GLfloat value = model->vertices[vi * 3 + ci];

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

		// Notice: The indeces in Obj files start from 1
		for (GLsizei vi = 1; vi < model->numvertices; vi++) {
			GLfloat value = model->vertices[vi * 3 + ci];

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


	// ==================
	//  Release Resource
	// ==================

	// Free GLM model data
	glmDelete(model);
}

Model::~Model() {
	// Traverse groups
	for (unsigned groupIndex = 0; groupIndex < _numGroups; groupIndex++) {
		// Release vertex and normal arrays
		delete[] _groups[groupIndex].vertices;
		delete[] _groups[groupIndex].normals;
	}

	// Release groups
	delete[] _groups;
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

void Model::draw(Matrix transformMatrix, GLint shVertices, GLint shNormals, GLint shMvpLoc) {
	GLfloat mvp[16];

	// Calculate MVP
	// MVP = T * R * S * N
	transformMatrix.postmultiply(_translation);
	transformMatrix.postmultiply(_rotation);
	transformMatrix.postmultiply(_scale);
	transformMatrix.postmultiply(_normalize);
	transformMatrix.outputAsColumnMajor(mvp);

	// Pass matrix and array pointers
	glVertexAttribPointer(shVertices, 3, GL_FLOAT, GL_FALSE, 0, _vertices);
	glVertexAttribPointer(shNormals, 3, GL_FLOAT, GL_FALSE, 0, _colors);
	glUniformMatrix4fv(shMvpLoc, 1, GL_FALSE, mvp);

	// draw the array we just bound
	glDrawElements(GL_TRIANGLES, _numTriangles * 3, GL_UNSIGNED_INT, (GLvoid*)_vIndices);
}

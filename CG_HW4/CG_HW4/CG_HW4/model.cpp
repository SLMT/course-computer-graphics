#include <float.h>
#include <stdio.h>
#include <string.h>

// Our libraries
#include "model.h"

// 3-party libraries
#include "GLM.h"
#include "texture.h"

#define SHINEINESS 100


void copyData(unsigned count, GLfloat *from, GLfloat *to) {
	for (unsigned i = 0; i < count; i++)
		to[i] = from[i];
}

void loadTexture(GLuint texId, char *texFileName) {
	unsigned long size;
	char temp;
	FileHeader fh;
	InfoHeader ih;
	FILE *file;
	char *image;
	char actualTexFileName[100];

	sprintf(actualTexFileName, "TextureModels/%s", texFileName);
	printf("Texture file: %s\n", actualTexFileName);

	// Read the file
	file = fopen(actualTexFileName, "rb");
	fread(&fh, sizeof(FileHeader), 1, file);
	fread(&ih, sizeof(InfoHeader), 1, file);
	size = ih.Width * ih.Height * 3; // IH.Width * IH.Height * 3
	image = new char[size*sizeof(char)];
	fread(image, size*sizeof(char), 1, file);
	fclose(file);

	// Swap channel => BRG----->RGB
	for (unsigned i = 0; i < size; i += 3) {
		temp = image[i];
		image[i] = image[i+2];
		image[i+2] = temp;
	}

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, texId);

	// SLMT: Create a Text2D texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ih.Width, ih.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// SLMT: Mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// Release the resource
	delete[] image;
}

Model::Model(char *fileName) {

	// ============
	//  Load model
	// ============

	// Load model
	GLMmodel *model = glmReadOBJ(fileName);

	// Auto generation for vertex normals
	if (model->numnormals == 0) {
		printf("There is no vertex normal in file %s. Auto generating for it.\n", fileName);
		glmFacetNormals(model);
		glmVertexNormals(model, 90.0);
	}

	// Allocate memory for groups
	_numGroups = model->numgroups;
	_groups = new MaterialGroup[_numGroups];

	// Traverse groups
	GLMgroup* group = model->groups;
	for (unsigned groupIndex = 0; groupIndex < _numGroups;
			group = group->next, groupIndex++) {
		// Get material data
		GLuint matIndex = group->material;
		GLMmaterial mat = model->materials[matIndex];

		copyData(4, mat.diffuse, _groups[groupIndex].diffuse);
		copyData(4, mat.ambient, _groups[groupIndex].ambient);
		copyData(4, mat.specular, _groups[groupIndex].specular);
		copyData(4, mat.emmissive, _groups[groupIndex].emmissive);
		// _groups[groupIndex].shininess = mat.shininess;
		_groups[groupIndex].shininess = SHINEINESS;

		// Get texture data
		if (strcmp(model->materials[matIndex].textureImageName, "") != 0) {
			glGenTextures(1, &(_groups[groupIndex].texId));
			loadTexture(_groups[groupIndex].texId, model->materials[matIndex].textureImageName);
			_groups[groupIndex].hasTexture = true;
		} else
			_groups[groupIndex].hasTexture = false;

		// Allocate memory for vertices, normals and texture coordinates
		GLuint numTri = group->numtriangles;
		_groups[groupIndex].numTriangles = numTri;
		_groups[groupIndex].vertices = new GLfloat[numTri * 3 * 3];
		_groups[groupIndex].normals = new GLfloat[numTri * 3 * 3];
		_groups[groupIndex].texCoord = new GLfloat[numTri * 3 * 3];

		// Get vertices, normals and texture coordinates
		for (GLuint triIndex = 0; triIndex < numTri; triIndex++) {
			// Get the triangle index in the GLM model
			GLuint glmTriIndex = group->triangles[triIndex];

			for (GLuint vecIndex = 0; vecIndex < 3; vecIndex++) {
				// Get the vectex index in the GLM model
				GLuint glmVecIndex = model->triangles[glmTriIndex].vindices[vecIndex];
				GLuint glmNorIndex = model->triangles[glmTriIndex].nindices[vecIndex];
				GLuint glmTextIndex = model->triangles[glmTriIndex].tindices[vecIndex];

				for (GLuint coordIndex = 0; coordIndex < 3; coordIndex++) {
					// Calculate the saving index
					GLuint vecSaveIndex = triIndex * 9 + vecIndex * 3 + coordIndex;
					GLuint texSaveIndex = triIndex * 6 + vecIndex * 2 + coordIndex;

					// Get data
					_groups[groupIndex].vertices[vecSaveIndex] =
						model->vertices[glmVecIndex * 3 + coordIndex];
					_groups[groupIndex].normals[vecSaveIndex] =
						model->normals[glmNorIndex * 3 + coordIndex];

					// Get texture coordinates (only 2 dimensions)
					if (coordIndex < 2) {
						_groups[groupIndex].texCoord[texSaveIndex] =
							model->texcoords[glmTextIndex * 2 + coordIndex];
					}
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
		for (unsigned vi = 1; vi < model->numvertices; vi++) {
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
		for (unsigned vi = 1; vi < model->numvertices; vi++) {
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

	// Texture parameters
	_texWrapMode = GL_REPEAT;
	_texMagFilter = GL_LINEAR;
	_texMinFilter = GL_LINEAR;

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

void Model::draw(Matrix transformMatrix, ShaderPointers shPos) {
	GLfloat mvp[16];

	// Calculate MVP
	// MVP = T * R * S * N
	transformMatrix.postmultiply(_translation);
	transformMatrix.postmultiply(_rotation);
	transformMatrix.postmultiply(_scale);
	transformMatrix.postmultiply(_normalize);
	transformMatrix.outputAsColumnMajor(mvp);

	// Pass matrix to the shader
	glUniformMatrix4fv(shPos.mvp, 1, GL_FALSE, mvp);
	
	// For each material groups
	for (unsigned i = 0; i < _numGroups; i++) {
		// Pass arrays and attributes to the shader
		glVertexAttribPointer(shPos.vertexPos, 3, GL_FLOAT, GL_FALSE, 0, _groups[i].vertices);
		glVertexAttribPointer(shPos.vertexNor, 3, GL_FLOAT, GL_FALSE, 0, _groups[i].normals);
		glVertexAttribPointer(shPos.texCoord, 2, GL_FLOAT, GL_FALSE, 0, _groups[i].texCoord);

		// Active the texture
		if (_groups[i].hasTexture) {
			glBindTexture(GL_TEXTURE_2D, _groups[i].texId);
			glUniform1i(shPos.havingTexture, 1);

			// Set texture parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _texWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _texWrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _texMinFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _texMagFilter);
		} else
			glUniform1i(shPos.havingTexture, 0);

		// Pass the lighting parameters
		glUniform4fv(shPos.matAmb, 1, _groups[i].ambient);
		glUniform4fv(shPos.matDiff, 1, _groups[i].diffuse);
		glUniform4fv(shPos.matSpec, 1, _groups[i].specular);
		glUniform1f(shPos.matShin, _groups[i].shininess);
	
		// draw the array we just bound
		glDrawArrays(GL_TRIANGLES, 0, _groups[i].numTriangles * 3);
	}
}

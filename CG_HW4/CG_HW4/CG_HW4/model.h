#ifndef MODEL_H
#define MODEL_H

// Our libraries
#include "shader.h"
#include "matrix.h"

// 3-party libraries
#include <GL/glew.h>

typedef struct s_material_group {
	// Vertex Info
	GLfloat *vertices, *normals, *texCoord;
	GLuint numTriangles;

	// Material Info
	GLfloat diffuse[4];
	GLfloat ambient[4];
	GLfloat specular[4];
	GLfloat emmissive[4];
	GLfloat shininess;

	// Texture Info
	GLuint texId;
	bool hasTexture;
} MaterialGroup;


class Model {
public:

	// Constructor
	Model(char *fileName);

	// Deconstructor
	~Model();

	// Transform functions
	void translate(GLfloat dx, GLfloat dy, GLfloat dz);
	void rotate(GLfloat theta, GLfloat x, GLfloat y, GLfloat z);
	void scale(GLfloat sx, GLfloat sy, GLfloat sz);
	inline void reset() {
		_translation = Matrix();
		_rotation = Matrix();
		_scale = Matrix();
	}

	// Render function
	void draw(Matrix transformMatrix, ShaderPointers shPos);

private:

	// Model data
	MaterialGroup *_groups;
	GLuint _numGroups;

	// Matrixes for rendering
	Matrix _normalize;
	Matrix _translation, _rotation, _scale;

	// Texture parameters
	GLint _texWrapMode;
	GLint _texMagFilter;
	GLint _texMinFilter;
};


#endif
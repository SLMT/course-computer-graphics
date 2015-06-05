#ifndef SHADER_H
#define SHADER_H

// 3-party libraries
#include <GL/glew.h>

typedef struct s_shader_pointers {
	// Model related
	GLint vertexPos, vertexNor;
	GLint mvp;
	
	// MaterialParameters
	GLint matAmb, matDiff,
		matSpec, matShin;

	// LightSourceParameters
	GLint dirEnabled, dirDirection, dirAmbient, dirColor;
	GLint posEnabled, posPosition, posAmbient, posColor;
	GLint spotEnabled, spotPosition, spotAmbient, spotColor,
		spotDirection, spotExponent, spotCosCutoff;

	// Texture parameters
	GLint texCoord, havingTexture;
} ShaderPointers;

#endif
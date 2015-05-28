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
	GLint lightAmb, lightDiff, lightSpec;
	GLint lightPos, lightHalfVec;
	GLint lightSpotDir, lightSpotExp,
		lightSpotCut, lightSpotCos;
	GLint lightConsAtt, lightLinAtt,
		lightQuadAtt;

} ShaderPointers;

#endif
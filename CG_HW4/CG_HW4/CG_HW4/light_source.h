#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <stdio.h>

// Our libraries
#include "shader.h"

// 3-party libraries
#include <GL/glew.h>

typedef enum e_light_type { Directional, Positional, SpotLight } LightType;

class LightSource {
public:

	// Constructors
	LightSource(LightType type, bool isEnabled);

	// Moving functions
	void rotateByX(GLfloat theta);
	void rotateByY(GLfloat theta);
	void rotateByZ(GLfloat theta);

	// Status controls
	inline void toggleEnableStatus() {
		_isEnabled = !_isEnabled;
	}

	// Spot light parameters
	inline void adjustSpotExp(GLfloat delta) {
		GLfloat tmp = _spotExp + delta;
		_spotExp = (tmp > 0.0f)? tmp : 0.0f;
		printf("Spot light exp: %f\n", _spotExp);
	}
	inline void adjustSpotCutoff(GLfloat delta) {
		GLfloat tmp = _spotCosCutoff + delta;
		_spotCosCutoff = (tmp > 0.0f)? tmp : 0.0f;
		printf("Spot light cutoff: %f\n", _spotCosCutoff);
	}

	// Render functions
	void linkShader(ShaderPointers shPos);

private:

	// Status
	bool _isEnabled;
	LightType _type;

	// Position
	GLfloat _position[3];

	// Color paramters
	GLfloat _ambient[4], _color[4];

	// Spot light parameters
	GLfloat _spotDirect[3], _spotExp, _spotCosCutoff;
};

#endif
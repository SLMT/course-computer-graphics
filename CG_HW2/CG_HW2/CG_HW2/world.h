#ifndef WORLD_H
#define WORLD_H

// Our libraries
#include "matrix.h"
#include "model.h"

// 3-party libraries
#include <GL/glew.h>

class World {
public:

	// Constructor
	World();

	// Render function
	void draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc);

private:

	Model *_models[5];
};

#endif
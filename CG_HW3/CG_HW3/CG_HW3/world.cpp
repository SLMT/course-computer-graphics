// Our libraries
#include "world.h"

World::World() {

	// Load models
	_models[0] = new Model("NormalModels/Low/boxN.obj");
	_models[1] = new Model("NormalModels/Low/dolphinN.obj");
	_models[2] = new Model("NormalModels/Medium/al7KN.obj");
	_models[3] = new Model("NormalModels/Medium/bunny5KN.obj");
	_models[4] = new Model("NormalModels/High/brain18KN.obj");
	_models[5] = new Model("NormalModels/High/lucy25KN.obj");
}

void World::draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc) {
	// Draw each model
	for (int i = 0; i < 5; i++)
		_models[i]->draw(transformMatrix, shPosLoc, shColLoc, shMvpLoc);
}

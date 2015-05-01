// Our libraries
#include "world.h"

World::World() {

	// Load models
	_models[0] = new Model("ColorModels/boxC.obj");
	_models[1] = new Model("ColorModels/bunny5KC.obj");
	_models[2] = new Model("ColorModels/dragon10KC.obj");
	_models[3] = new Model("ColorModels/lucy25KC.obj");
	_models[4] = new Model("ColorModels/triangleC.obj");
	
	// Transform models
	_models[1]->translate(3, 3, 0);
	_models[2]->translate(3, -3, 0);
	_models[3]->translate(-3, 3, 0);
	_models[4]->translate(-3, -3, 0);
}

void World::draw(Matrix transformMatrix, GLint shPosLoc, GLint shColLoc, GLint shMvpLoc) {
	// Draw each model
	for (int i = 0; i < 5; i++)
		_models[i]->draw(transformMatrix, shPosLoc, shColLoc, shMvpLoc);
}

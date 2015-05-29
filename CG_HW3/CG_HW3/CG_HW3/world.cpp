// Our libraries
#include "world.h"

World::World() {

	// Initialize variables
	_currentModelIndex = 0;

	// Lighting
	_lights[0] = new LightSource(Directional, false);
	_lights[1] = new LightSource(Positional, false);
	_lights[2] = new LightSource(SpotLight, true);

	// Load models
	_models[0] = new Model("NormalModels/Low/boxN.obj");
	_models[1] = new Model("NormalModels/Low/dolphinN.obj");
	_models[2] = new Model("NormalModels/Medium/al7KN.obj");
	_models[3] = new Model("NormalModels/Medium/bunny5KN.obj");
	_models[4] = new Model("NormalModels/High/brain18KN.obj");
	_models[5] = new Model("NormalModels/High/lucy25KN.obj");
}

void World::draw(Matrix transformMatrix, ShaderPointers shPos) {
	// Set up the light source
	for (int i = 0; i < NUM_LIGHTS; i++)
		_lights[i]->linkShader(shPos);

	// Draw each model
	_models[_currentModelIndex]->draw(transformMatrix, shPos);
}

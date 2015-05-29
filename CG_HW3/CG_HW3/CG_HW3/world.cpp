// Our libraries
#include "world.h"

World::World() {

	// Initialize variables
	_currentModelIndex = 0;

	// Lighting
	_lights[0] = new LightSource(Directional, true);
	_lights[1] = new LightSource(Positional, false);
	_lights[2] = new LightSource(SpotLight, false);

	// Load models
	_models[0] = new Model("NormalModels/Low/boxN.obj");
	_models[1] = new Model("NormalModels/Low/dodecahedronN.obj");
	_models[2] = new Model("NormalModels/Low/dolphinN.obj");
	_models[3] = new Model("NormalModels/Low/icosahedronN.obj");
	_models[4] = new Model("NormalModels/Low/octahedronN.obj");
	_models[5] = new Model("NormalModels/Low/shuttleN.obj");
	_models[6] = new Model("NormalModels/Low/sphereN.obj");
	_models[7] = new Model("NormalModels/Low/tetrahedronN.obj");
	_models[8] = new Model("NormalModels/Low/tigerN.obj");

	_models[9] = new Model("NormalModels/Medium/al7KN.obj");
	_models[10] = new Model("NormalModels/Medium/bunny5KN.obj");
	_models[12] = new Model("NormalModels/Medium/cessna7KN.obj");
	_models[13] = new Model("NormalModels/Medium/cow3KN.obj");
	_models[14] = new Model("NormalModels/Medium/duck4KN.obj");
	_models[15] = new Model("NormalModels/Medium/frog2KN.obj");
	_models[16] = new Model("NormalModels/Medium/heptoroid8KN.obj");
	_models[17] = new Model("NormalModels/Medium/horse5KN.obj");
	_models[18] = new Model("NormalModels/Medium/laurana2KN.obj");
	_models[19] = new Model("NormalModels/Medium/Nala6KN.obj");
	_models[20] = new Model("NormalModels/Medium/santa7KN.obj");
	_models[21] = new Model("NormalModels/Medium/teapot4KN.obj");

	_models[22] = new Model("NormalModels/High/armadillo12KN.obj");
	_models[23] = new Model("NormalModels/High/brain18KN.obj");
	_models[24] = new Model("NormalModels/High/Dino20KN.obj");
	_models[25] = new Model("NormalModels/High/dragon10KN.obj");
	_models[26] = new Model("NormalModels/High/elephant16KN.obj");
	_models[27] = new Model("NormalModels/High/happy10KN.obj");
	_models[28] = new Model("NormalModels/High/hippo23KN.obj");
	_models[29] = new Model("NormalModels/High/igea17KN.obj");
	_models[30] = new Model("NormalModels/High/lion12KN.obj");
	_models[31] = new Model("NormalModels/High/lucy25KN.obj");
	_models[32] = new Model("NormalModels/High/maxplanck20KN.obj");
	_models[33] = new Model("NormalModels/High/texturedknot11KC.obj");
}

void World::draw(Matrix transformMatrix, ShaderPointers shPos) {
	// Set up the light source
	for (int i = 0; i < NUM_LIGHTS; i++)
		_lights[i]->linkShader(shPos);

	// Draw each model
	_models[_currentModelIndex]->draw(transformMatrix, shPos);
}

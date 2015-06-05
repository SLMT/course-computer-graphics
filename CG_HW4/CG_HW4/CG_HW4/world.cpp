#include <stdio.h>

// Our libraries
#include "world.h"

char* modelFiles[NUM_MODELS] = 
{
	"TextureModels/teemo.obj",
	"TextureModels/satellitetrap.obj",
	"TextureModels/morgana_fallenangel.obj",
	"TextureModels/ahri_pop.obj",
	"TextureModels/katarina_referee.obj",

	"TextureModels/nidalee_cat_2012.obj",
	"TextureModels/duck.obj",
	"TextureModels/ball.obj",
	"TextureModels/Dog.obj",
	"TextureModels/ZEBRA.obj",

	"TextureModels/Digda.obj",
	"TextureModels/Fushigidane.obj",
	"TextureModels/Golonya.obj",
	"TextureModels/Hitokage.obj",
	"TextureModels/laurana500.obj",

	"TextureModels/Mew.obj",
	"TextureModels/Nala.obj",
	"TextureModels/Nyarth.obj",
	"TextureModels/texturedknot.obj",
	"TextureModels/Zenigame.obj",

	"TextureModels/cube.obj",
};

World::World() {

	// Initialize variables
	_currentModelIndex = 0;

	// Lighting
	_lights[0] = new LightSource(Directional, true);
	_lights[1] = new LightSource(Positional, false);
	_lights[2] = new LightSource(SpotLight, false);

	// Load models
	for (unsigned i = 0; i < 1; i++) {
		printf("Loading model file: %s\n", modelFiles[i]);
		_models[i] = new Model(modelFiles[i]);
	}
}

void World::draw(Matrix transformMatrix, ShaderPointers shPos) {
	// Set up the light source
	for (int i = 0; i < NUM_LIGHTS; i++)
		_lights[i]->linkShader(shPos);

	// Draw each model
	_models[_currentModelIndex]->draw(transformMatrix, shPos);
}

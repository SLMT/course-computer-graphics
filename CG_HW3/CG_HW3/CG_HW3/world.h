#ifndef WORLD_H
#define WORLD_H

// Our libraries
#include "shader.h"
#include "matrix.h"
#include "model.h"
#include "light_source.h"

// 3-party libraries
#include <GL/glew.h>

#ifndef NUM_MODELS
#define NUM_MODELS 6
#endif

class World {
public:

	// Constructor
	World();

	// World Control
	inline void nextModel() {
		_currentModelIndex = (_currentModelIndex + 1) % NUM_MODELS;
	}

	// Getters
	inline Model* getCurrentModel() {
		return _models[_currentModelIndex];
	}
	inline LightSource* getLigthSource() {
		return _light;
	}

	// Render function
	void draw(Matrix transformMatrix, ShaderPointers shPos);

private:

	unsigned _currentModelIndex;
	Model *_models[NUM_MODELS];
	LightSource *_light;

};

#endif
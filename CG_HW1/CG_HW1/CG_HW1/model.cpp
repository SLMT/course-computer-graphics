/************************************
	Purpose:
		Model-related functions
	Author: SLMT
************************************/
// Original Libraries
#include <stdio.h>
#include <float.h>

// OpenGL-related Libraries
#include <freeglut/glut.h>

// Third-party Libraries
#include "GLM.h"

// My Header Files
#include "cg_hw1.h"

// Model Files
unsigned global_obj_files_num = 33;
char *global_obj_files[] = {
	// Low
	"ColorModels/Low/boxC.obj",
	"ColorModels/Low/dodecahedronC.obj",
	"ColorModels/Low/dolphinC.obj",
	"ColorModels/Low/icosahedronC.obj",
	"ColorModels/Low/octahedronC.obj",
	"ColorModels/Low/shuttleC.obj",
	"ColorModels/Low/sphereC.obj",
	"ColorModels/Low/tetrahedronC.obj",
	"ColorModels/Low/tigerC.obj",

	// Medium
	"ColorModels/Medium/al7KC.obj",
	"ColorModels/Medium/bunny5KC.obj",
	"ColorModels/Medium/cessna7KC.obj",
	"ColorModels/Medium/cow3KC.obj",
	"ColorModels/Medium/duck4KC.obj",
	"ColorModels/Medium/frog2KC.obj",
	"ColorModels/Medium/heptoroid8KC.obj",
	"ColorModels/Medium/horse5KC.obj",
	"ColorModels/Medium/laurana2KC.obj",
	"ColorModels/Medium/nala6KC.obj",
	"ColorModels/Medium/santa7KC.obj",
	"ColorModels/Medium/teapot4KC.obj",

	// High
	"ColorModels/High/armadillo12KC.obj",
	"ColorModels/High/brain18KC.obj",
	"ColorModels/High/dino20KC.obj",
	"ColorModels/High/dragon10KC.obj",
	"ColorModels/High/elephant16KC.obj",
	"ColorModels/High/happy10KC.obj",
	"ColorModels/High/hippo23KC.obj",
	"ColorModels/High/igea17KC.obj",
	"ColorModels/High/lion12KC.obj",
	"ColorModels/High/lucy25KC.obj",
	"ColorModels/High/maxplanck20KC.obj",
	"ColorModels/High/texturedknot11KC.obj"
};


void normalize(GLMmodel* model)
{
	// Find the longest distance to the center
	GLfloat max_diff = 0;
	for (int ci = 0; ci < 3; ci++) {
		GLfloat max = FLT_MIN, min = FLT_MAX;

		for (int vi = 1; vi <= (int) model->numvertices; vi++) {
			GLfloat value = model->vertices[vi * 3 + ci];

			if (max < value)
				max = value;

			if (min > value)
				min = value;
		}

		// printf("Min: %f, Max: %f\n", min, max);

		GLfloat diff = (max - min) / 2;
		if (max_diff < diff)
			max_diff = diff;
	}

	// Scale
	GLfloat ratio = 1.0f / max_diff;
	for (int vi = 1; vi <= (int) model->numvertices; vi++) {
		for (int ci = 0; ci < 3; ci++) {
			model->vertices[vi * 3 + ci] *= ratio;
		}
	}

	// Find the center
	GLfloat center[3];
	for (int ci = 0; ci < 3; ci++) {
		GLfloat max = FLT_MIN, min = FLT_MAX;

		for (int vi = 1; vi <= (int) model->numvertices; vi++) {
			GLfloat value = model->vertices[vi * 3 + ci];

			if (max < value)
				max = value;

			if (min > value)
				min = value;
		}

		center[ci] = (max + min) / 2;
	}

	// Shift
	for (int vi = 1; vi <= (int) model->numvertices; vi++)
		for (int ci = 0; ci < 3; ci++)
			model->vertices[vi * 3 + ci] -= center[ci];
}

GLMmodel* loadOBJModel(char *filename)
{
	// read an obj model here
	GLMmodel* model = glmReadOBJ(filename);

	// normalize model
	normalize(model);

	return model;
}
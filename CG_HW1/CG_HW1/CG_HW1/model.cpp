/************************************
	Purpose:
		Model-related functions
	Author: SLMT
************************************/
// Original Libraries
#include <stdio.h>
#include <stdlib.h>

// OpenGL-related Libraries
#include <freeglut/glut.h>

// Third-party Libraries
#include "GLM.h"

// My Header Files
#include "cg_hw1.h"


void colorModel(GLMmodel* model)
{
	int i;

	// TODO:
	//// You should traverse the vertices and the colors of each vertex. 
	//// Normalize each vertex into [-1, 1], which will fit the camera clipping window.

	// The center position of the model 
	// (should be calculated by yourself)
	model->position[0];
	model->position[1];
	model->position[2];

	/*
	for(i = 0; i < (int) model->numtriangles; i++)
	{
		// the index of each vertex
		int indv1 = model->triangles[i].vindices[0];
		int indv2 = model->triangles[i].vindices[1];
		int indv3 = model->triangles[i].vindices[2];

		// the index of each color
		int indc1 = indv1;
		int indc2 = indv2;
		int indc3 = indv3;

		// vertices
		global_vertices[i*9+0] = model->vertices[indv1*3+0];
		global_vertices[i*9+1] = model->vertices[indv1*3+1];
		global_vertices[i*9+2] = model->vertices[indv1*3+2];

		global_vertices[i*9+3] = model->vertices[indv2*3+0];
		global_vertices[i*9+4] = model->vertices[indv2*3+1];
		global_vertices[i*9+5] = model->vertices[indv2*3+2];

		global_vertices[i*9+6] = model->vertices[indv3*3+0];
		global_vertices[i*9+7] = model->vertices[indv3*3+1];
		global_vertices[i*9+8] = model->vertices[indv3*3+2];

		// colors
		GLfloat c1, c2, c3;
		c1 = model->colors[indv1*3+0];
		c2 = model->colors[indv1*3+1];
		c3 = model->colors[indv1*3+2];

		c1 = model->colors[indv2*3+0];
		c2 = model->colors[indv2*3+1];
		c3 = model->colors[indv2*3+2];

		c1 = model->colors[indv3*3+0];
		c2 = model->colors[indv3*3+1];
		c3 = model->colors[indv3*3+2];
	}
	*/
}

GLMmodel* loadOBJModel(char *filename)
{
	printf("Read obj file %s\n", filename);

	// read an obj model here
	GLMmodel* model = glmReadOBJ(filename);

	// traverse the color model
	colorModel(model);

	return model;
}
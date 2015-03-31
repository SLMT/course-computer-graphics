/************************************
	Purpose:
		GL render functions
	Author: SLMT
************************************/
// Original Libraries
#include <stdio.h>

// OpenGL-related Libraries
#include <GL/glew.h>
#include <freeglut/glut.h>

// Third-party Libraries
#include "textfile.h"

// My Header Files
#include "cg_hw1.h"

// Global variables
GLMmodel* global_current_model = NULL;
GLint global_pos_loc, global_color_loc;
bool global_flag_is_solid = true;

void idle(void)
{
	glutPostRedisplay();
}

void renderModel(void) {
	int i;
	GLfloat vertex[9], color[9];

	glEnableVertexAttribArray(global_pos_loc);
	glEnableVertexAttribArray(global_color_loc);

	for(i = 0; i < (int) global_current_model->numtriangles; i++)
	{
		// the index of each vertex
		int indv1 = global_current_model->triangles[i].vindices[0];
		int indv2 = global_current_model->triangles[i].vindices[1];
		int indv3 = global_current_model->triangles[i].vindices[2];

		// the index of each color
		int indc1 = indv1;
		int indc2 = indv2;
		int indc3 = indv3;

		// vertices
		vertex[0] = global_current_model->vertices[indv1*3+0];
		vertex[1] = global_current_model->vertices[indv1*3+1];
		vertex[2] = global_current_model->vertices[indv1*3+2];

		vertex[3] = global_current_model->vertices[indv2*3+0];
		vertex[4] = global_current_model->vertices[indv2*3+1];
		vertex[5] = global_current_model->vertices[indv2*3+2];

		vertex[6] = global_current_model->vertices[indv3*3+0];
		vertex[7] = global_current_model->vertices[indv3*3+1];
		vertex[8] = global_current_model->vertices[indv3*3+2];

		// colors
		color[0] = global_current_model->colors[indv1*3+0];
		color[1] = global_current_model->colors[indv1*3+1];
		color[2] = global_current_model->colors[indv1*3+2];

		color[3] = global_current_model->colors[indv2*3+0];
		color[4] = global_current_model->colors[indv2*3+1];
		color[5] = global_current_model->colors[indv2*3+2];

		color[6] = global_current_model->colors[indv3*3+0];
		color[7] = global_current_model->colors[indv3*3+1];
		color[8] = global_current_model->colors[indv3*3+2];

		glVertexAttribPointer(global_pos_loc, 3, GL_FLOAT, GL_FALSE, 0, vertex);
		glVertexAttribPointer(global_color_loc, 3, GL_FLOAT, GL_FALSE, 0, color);

		// draw the array we just bound
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

void renderScene(void)
{
	// Clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render Mode
	if (global_flag_is_solid)
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	// Render model
	renderModel();

	// Swap
	glutSwapBuffers();
}

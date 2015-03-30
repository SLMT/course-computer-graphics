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
GLMmodel *global_current_model;
GLint global_pos_loc, global_color_loc;
GLfloat *global_vertices, *global_colors;


void idle(void)
{
	glutPostRedisplay();
}

void renderScene(void)
{
	// clear canvas
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableVertexAttribArray(global_pos_loc);
	glEnableVertexAttribArray(global_color_loc);

	// set pointers
	glVertexAttribPointer(global_pos_loc, 3, GL_FLOAT, GL_FALSE, 0, global_vertices);
	glVertexAttribPointer(global_color_loc, global_current_model->numtriangles * 3, GL_FLOAT, GL_FALSE, 0, global_colors);

	// draw the array we just bound
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

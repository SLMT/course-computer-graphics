/************************************
	Purpose:
		The entry point of this program.
	Author: SLMT
************************************/
// Original Libraries
#include <stdio.h>

// OpenGL-related Libraries
#include <GL/glew.h>
#include <freeglut/glut.h>

// My Header Files
#include "cg_hw1.h"

int main(int argc, char **argv) {

	// --------------------------
	//  initialze all components
	// --------------------------

	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	

	// create window
	glutInitWindowPosition(460, 40);
	glutInitWindowSize(800, 800);
	glutCreateWindow("SLMT's CG HW1");

	// glew init
	glewInit();
	if(glewIsSupported("GL_VERSION_2_0")) {
		printf("Ready for OpenGL 2.0\n");
	} else {
		printf("OpenGL 2.0 not supported\n");
		system("pause");
		exit(1);
	}

	// gl init
	glEnable(GL_DEPTH_TEST);
	setShaders();

	// load obj models
	global_current_model = loadOBJModel("ColorModels/bunny5KC.obj");


	// -------------------------
	//  register event handlers
	// -------------------------

	glutDisplayFunc (renderScene);
	glutIdleFunc    (idle);
	glutKeyboardFunc(onKeyboardEvent);
	glutMouseFunc   (onMouseEvent);
	glutMotionFunc  (onMouseMove);


	// ------
	//  main 
	// ------

	// main loop
	glutMainLoop();


	// ----------
	//  clean up 
	// ----------

	// free
	glmDelete(global_current_model);

	return 0;
}
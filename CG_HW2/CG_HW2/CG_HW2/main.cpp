#include <stdio.h>

// Our libraries
#include "main.h"

char filename[] = "ColorModels/bunny5KC.obj";
//char filename[] = "ColorModels/boxC.obj";
//char filename[] = "ColorModels/triangleC.obj";

int main(int argc, char **argv) {
	// glut init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// create window
	glutInitWindowPosition(460, 40);
	glutInitWindowSize(800, 800);
	glutCreateWindow("SLMT's CG HW2");

	glewInit();
	if(glewIsSupported("GL_VERSION_2_0")){
		printf("Ready for OpenGL 2.0\n");
	}else{
		printf("OpenGL 2.0 not supported\n");
		system("pause");
		exit(1);
	}

	// load models through glm
	currentModel = new Model(filename);

	// register glut callback functions
	glutDisplayFunc (onRender);
	glutIdleFunc    (onIdle);
	glutKeyboardFunc(onKeyboardEvent);
	glutMouseFunc   (onMouseEvent);
	glutMotionFunc  (onMouseMotionEvent);

	glEnable(GL_DEPTH_TEST);

	// set up shaders here
	setShaders();

	// main loop
	glutMainLoop();

	delete currentModel;

	return 0;
}


#include <stdio.h>
#include <float.h>

// Our libraries
#include "main.h"

// Define wheel motion
#ifndef GLUT_WHEEL_UP
	#define GLUT_WHEEL_UP   0x0003
	#define GLUT_WHEEL_DOWN 0x0004
#endif

#define DELTA 0.1f

// Flags
int pressX = -1, pressY = -1;
unsigned selectedLight = 0;

void onMouseEvent(int who, int state, int x, int y) {
	GLfloat scaleValue = 0.0f;

	// Which button
	switch(who){
	case GLUT_WHEEL_UP:
		scaleValue = 1.0f + DELTA;
		world->getCurrentModel()->scale(scaleValue, scaleValue, scaleValue);
		break;
	case GLUT_WHEEL_DOWN:
		scaleValue = 1.0f - DELTA;
		world->getCurrentModel()->scale(scaleValue, scaleValue, scaleValue);
		break;
	}

	// Button states
	switch(state){
	case GLUT_DOWN:
		// Save press position
		pressX = x;
		pressY = y;
		break;
	case GLUT_UP:
		break;
	}
}

void onMouseDragEvent(int x, int y) {
	static int lastX, lastY;

	// Calculate values
	GLfloat dx = (GLfloat) (x - lastX);
	GLfloat dy = (GLfloat) (y - lastY);

	// Check if it was the first time moving after pressing button
	if (pressX != -1 && pressY != -1) {
		dx = (GLfloat) (x - pressX);
		dy = (GLfloat) (y - pressY);
		pressX = -1;
		pressY = -1;
	}

	// Rotate
	if (dx > 0 + FLT_EPSILON || dx < 0 - FLT_EPSILON)
		world->getCurrentModel()->rotate(dx / 10, 0, 1, 0);
	if (dy > 0 + FLT_EPSILON || dy < 0 - FLT_EPSILON)
		world->getCurrentModel()->rotate(-dy / 10, 1, 0, 0);

	// Save the location
	lastX = x;
	lastY = y;
}

void onKeyboardEvent(unsigned char key, int x, int y) {
	switch(key) {
		// ESC
		case 27:
			exit(0); 
			break;

		// Switch model
		case 'M':
		case 'm':
			world->nextModel();
			break;

		// Moving
		case 'A':
		case 'a':
			world->getLigthSource(selectedLight)->rotateByY(-5);
			break;
		case 'D':
		case 'd':
			world->getLigthSource(selectedLight)->rotateByY(5);
			break;
		case 'W':
		case 'w':
			world->getLigthSource(selectedLight)->rotateByX(-5);
			break;
		case 'S':
		case 's':
			world->getLigthSource(selectedLight)->rotateByX(5);
			break;

		// Open or close
		case 'L':
		case 'l':
			world->getLigthSource(selectedLight)->toggleEnableStatus();
			break;

		// Select lights
		case 'I':
		case 'i':
			selectedLight = 0;
			printf("Now select the directional light source\n");
			break;
		case 'O':
		case 'o':
			selectedLight = 1;
			printf("Now select the positional light source\n");
			break;
		case 'P':
		case 'p':
			selectedLight = 2;
			printf("Now select the spot light source\n");
			break;

		// Spot light control
		case 'Z':
		case 'z':
			world->getLigthSource(2)->adjustSpotExp(0.1f);
			break;
		case 'X':
		case 'x':
			world->getLigthSource(2)->adjustSpotExp(-0.1f);
			break;
		case 'C':
		case 'c':
			world->getLigthSource(2)->adjustSpotCutoff(0.01f);
			break;
		case 'V':
		case 'v':
			world->getLigthSource(2)->adjustSpotCutoff(-0.01f);
			break;
		
		// Lighting 
		case 'Q':
		case 'q':
			isVertexLighting = !isVertexLighting;
			break;

		// Texture 
		case 'T':
		case 't':
			world->getCurrentModel()->toggleWrapMode();
			break;
		case 'Y':
		case 'y':
			world->getCurrentModel()->toggleFilter();
			break;

		// Help
		case 'H':
		case 'h':
			printf("==================== Help ====================\n");
			printf("Select the light source first,\n");
			printf("I: Directional Light Source\n");
			printf("O: Point Light Source\n");
			printf("P: Spot Light Source\n\n");
			printf("then use the follwing controls: \n");
			printf("A/D: Move left/right\n");
			printf("W/S: Move up/down\n");
			printf("L: Turn on/off the selected light source\n");
			printf("Z/X: Adjust the exponent value of spot light\n");
			printf("C/V: Adjust the cutoff value of spot light\n\n");
			printf("Q: Toggle vertex and fragment lighting\n\n");
			printf("T: Toggle texture wrap mode\n\n");
			printf("Y: Toggle texture mag/min filter\n\n");
			printf("M: Next model\n");
			printf("H: Help List\n");
			break;
	}
}
